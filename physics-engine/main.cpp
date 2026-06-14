#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"EBO.h"
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
// source code for the shaders


// size of the window
const GLint width = 800, height = 800;


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
		//       cordinates								/  colors		
		-0.5f  ,-0.5f * float(sqrt(3))  / 3    ,0.0f,    0.8 ,0.3f,  0.02f,//lower left conrer
		 0.5f  ,-0.5f * float(sqrt(3))  / 3    ,0.0f,    0.8f,0.3f , 0.02f,//lower right corner
		 0.0f  , 0.5f * float(sqrt(3))  * 2 / 3,0.0f,    0.0f,0.6f , 0.32f,//upper corner
		-0.25f , 0.5f * float(sqrt(3))  / 6    ,0.0f,    0.1f,0.45f,0.77f,//inner left 
		 0.25f , 0.5f * float(sqrt(3))  / 6    ,0.0f,    0.1f,0.45f,0.77f,//inner right 
		 0.0f  ,-0.5f * float(sqrt(3))  / 3    ,0.0f,    0.8f,0.3f , 0.02f //inner down

	};

	GLuint indices[] = {
		0,3,5,
		3,2,4,
		5,4,1
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

	//running the shaderprogram function
	Shader shaderProgram("default.vert", "default.frag");

	//bindin vao1
	VAO VAO1;
	VAO1.Bind();

	//refrencing vertices to VBO EBO
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//main loop


	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//use the shader program ,bind the array,and the draw the triangle
		shaderProgram.Activate();
		glUniform1f(uniID,0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);


	}




	//cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}