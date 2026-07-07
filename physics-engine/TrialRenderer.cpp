#include"TrailRenderer.h"
#include"CelestialBody.h"
#include"Constants.h"

#include<GL/glew.h>
#include<glm/glm.hpp>

void TrailRenderer::Draw(const CelestialBody& body, Shader& shader, Camera& camera) {
	if (body.trail.size() < 2)
		return;
	shader.Activate();
	shader.SetVec3("trailColor", body.trailSettings.color);
	camera.Matrix(shader, "camMatrix");


	size_t startIndex = 0;

	if (body.trail.size() > body.trailSettings.displayedPoints)
	{
		startIndex = body.trail.size() - body.trailSettings.displayedPoints;
	}
	std::vector<glm::vec3> vertices;
	vertices.reserve(body.trail.size()-startIndex);
	for (size_t i = startIndex;i < body.trail.size();i++) {
		glm::dvec3 point = body.trail[i];
		point /= Constants::Rendering::DistanceScale;

		vertices.push_back(glm::vec3(point));
	}
	vbo.Update(vertices);

	vao.Bind();

	glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(vertices.size()));

	vao.Unbind();
}

TrailRenderer::TrailRenderer() {
	vao.Bind();
	vbo.Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	vao.Unbind();
	vbo.Unbind();
}
