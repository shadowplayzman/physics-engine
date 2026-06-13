#include "ShaderClass.h"
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// defining the vertex shader 
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexSource, NULL);
	glCompileShader(vertexshader);

	// defining the fragment shader 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//create shader program which will render the triangle
	ID = glCreateProgram();

	//link vertex and fragment shader to the shader program
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// delete the vertex and fragment shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);

}

void Shader::Delete() {
	glDeleteProgram(ID);
}