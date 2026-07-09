#include"SkyBox.h"
#include<stb_image.h>
#include<iostream>

static const float skyboxVertices[] =
{
	// positions

	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

Skybox::Skybox(const std::vector<std::string>& faces):shader("skybox.vert","skybox.frag") {
	SetupMesh();
	cubemapTexture = LoadCubemap(faces);
}
void Skybox::Draw(Camera& camera)
{
	shader.Activate();

	// Draw the skybox behind everything else
	glDepthFunc(GL_LEQUAL);

	// Remove camera translation so the skybox follows the camera
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));


	glm::mat4 projection = camera.GetProjectionMatrix();

	glUniformMatrix4fv(
		glGetUniformLocation(shader.ID, "view"),
		1,
		GL_FALSE,
		glm::value_ptr(view));

	glUniformMatrix4fv(
		glGetUniformLocation(shader.ID, "projection"),
		1,
		GL_FALSE,
		glm::value_ptr(projection));

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

	glUniform1i(
		glGetUniformLocation(shader.ID, "skybox"),
		0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

GLuint Skybox::LoadCubemap(const std::vector<std::string>& faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, channels;

	stbi_set_flip_vertically_on_load(false);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data =
			stbi_load(faces[i].c_str(), &width, &height, &channels, 0);

		if (data)
		{
			GLenum format = GL_RGB;

			if (channels == 4)
				format = GL_RGBA;
			else if (channels == 1)
				format = GL_RED;

			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				format,
				width,
				height,
				0,
				format,
				GL_UNSIGNED_BYTE,
				data);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load cubemap face: "
				<< faces[i] << std::endl;

			std::cout << stbi_failure_reason() << std::endl;
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_WRAP_S,
		GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_WRAP_T,
		GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_WRAP_R,
		GL_CLAMP_TO_EDGE);

	return textureID;
}

void Skybox::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}