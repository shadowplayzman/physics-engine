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
	//storing the contents of vertex anf fragment file into the variables
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//turning the contents to a string
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// defining the vertex shader 
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexSource, NULL);
	glCompileShader(vertexshader);
	//compileErrors(vertexshader, "VERTEX");

	// defining the fragment shader 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	//compileErrors(fragmentShader, "FRAGMENT");

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

void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infolog[1024];
	if (type != "program") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infolog << "\n " << std::endl;
		}
		else {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {
				glGetShaderInfoLog(shader, 1024, NULL, infolog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infolog << "\n " << std::endl;
			}
		}
	}
}