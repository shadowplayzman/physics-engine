#include"Texture.h"

Texture::Texture(const char* image, const char* textype, GLuint slot) {
	type = textype;
	//textures
	int widthImg, heightImg, numColch;
	//flips the image
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColch, 0);
	if (!bytes)
	{
		std::cout << "Failed to load texture: " << image << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		throw std::runtime_error("Texture loading failed");
	}

	//generate and binding the texture to the variable
	GLuint texture;
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0+slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	//gl nearest preseves the pixels and linear generate pixels based on the existing pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (numColch == 4) {
		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes);
	}
	else if (numColch == 3) {
		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGB,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes);
	}
	else if (numColch == 1) {
		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes);
	}
	else
	{
		throw std::invalid_argument("Automatic Texture type recongitniton failed");
	}
	

	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texunit(Shader& shader, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);

}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}