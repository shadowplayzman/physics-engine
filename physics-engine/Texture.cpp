#include"Texture.h"

Texture::Texture(const char* image, GLenum textype, GLuint slot, GLenum format, GLenum pixeltype) {
	type = textype;
	//textures
	int widthImg, heightImg, numColch;
	//flips the image
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColch, 4);

	//generate and binding the texture to the variable
	GLuint texture;
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0+slot);
	unit = slot;
	glBindTexture(textype, ID);

	//gl nearest preseves the pixels and linear generate pixels based on the existing pixels
	glTexParameteri(textype, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textype, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(textype, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textype, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textype, 0, GL_RGBA, widthImg, heightImg, 0, format, pixeltype, bytes);

	glGenerateMipmap(textype);


	stbi_image_free(bytes);
	glBindTexture(textype, 0);
}

void Texture::texunit(Shader& shader, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);

}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}