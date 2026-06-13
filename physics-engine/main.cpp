#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// source code for the shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 Fragcolor;\n"
"void main()\n"
"{\n"
"Fragcolor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

// size of the window
const GLint width = 800, height = 600;


int main() {

	//intinialize GLFW
	if (!glfwInit()) {
		std::cout << "glfw failed to intinialize";
		glfwTerminate();
		return 1;
	}

	//set up window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//defining the vertices of the triangle
	GLfloat vertices[] = {

		-0.5f  ,-0.5f * float(sqrt(3))  / 3,0.0f,//lower left conrer
		 0.5f  ,-0.5f * float(sqrt(3))  / 3,0.0f,//lower right corner
		-0.5f  , 0.5f * float(sqrt(3)) * 2 / 3,0.0f,//upper left corner
		 0.5f  , 0.5f * float(sqrt(3))  * 2 / 3,0.0f,//upper right corner
	};

	GLuint indices[] = {
		0,1,2,
		3,2,1
	};

	// create window
	GLFWwindow* window = glfwCreateWindow(width, height, "Physics Engine", NULL, NULL);

	if (!window) {
		std::cout << "failed to create window" << "\n";
		glfwTerminate();
		return 1;
	}

	//Get frame buffer size
	int bufferwidth = 800, bufferheight = 800;
	glfwGetFramebufferSize(window, &bufferwidth, &bufferheight);

	//set context
	glfwMakeContextCurrent(window);

	//Init GLew
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "glew failed to intinialize" << "\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;

	}

	//viewport
	glViewport(0, 0, bufferwidth, bufferheight);

	// defining the vertex shader 
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);

	// defining the fragment shader 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//create shader program which will render the triangle
	GLuint ShaderProgram = glCreateProgram();

	//link vertex and fragment shader to the shader program
	glAttachShader(ShaderProgram, vertexshader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);

	// delete the vertex and fragment shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentShader);

	//creating the vertix array object and buffer object
	GLuint VAO, VBO, EBO;

	// use the values of vetex array and buffer into vao and vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//data for the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//data for the vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	//main loop


	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//use the shader program ,bind the array,and the draw the triangle
		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);


	}




	//cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(ShaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}