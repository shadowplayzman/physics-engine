#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

//this will read the defualt files and get the contents
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type);
};


#endif // !SHADER_CLASS_H

