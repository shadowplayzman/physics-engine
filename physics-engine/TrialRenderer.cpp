#include"TrailRenderer.h"
#include"CelestialBody.h"
#include"Constants.h"

#include<GL/glew.h>
#include<glm/glm.hpp>

void TrailRenderer::Draw(const CelestialBody& body, Shader& shader, Camera& camera) {
	if (body.trail.size() < 2)
		return;
	shader.Activate();
	camera.Matrix(shader, "camMatrix");

	std::vector<glm::vec3> vertices;
	vertices.reserve(body.trail.size());

	for (const glm::dvec3& point : body.trail) {
		glm::dvec3 renderPoint = point / Constants::Rendering::DistanceScale;

		vertices.push_back(glm::vec3(renderPoint));
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
