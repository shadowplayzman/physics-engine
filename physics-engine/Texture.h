#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<GL/glew.h>
#include<stb_image.h>

#include"ShaderClass.h"

class Texture {
public:
	GLuint ID;
	GLenum type;
	GLuint unit;
	Texture(const char* image, GLenum textype, GLuint slot, GLenum format, GLenum pixeltype);

	void texunit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};



#endif