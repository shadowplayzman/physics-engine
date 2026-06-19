#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h" 
#include"EBO.h"
#include"ShaderClass.h"
#include"VAO.h"
#include"Camera.h"
#include"VBO.h"


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
		//       cordinates		/  colors				/texcord
		-0.5f  , 0.0f  , 0.5f,    0.83f, 0.70f , 0.44f,    0.0f,0.0f,//lower left conrer
		-0.5f  , 0.0f  ,-0.5f,    0.83f, 1.0f  , 0.44f,    5.0f,0.0f,//upper left corner
		 0.5f  , 0.0f  ,-0.5f,    0.83f, 0.70f , 0.44f,    0.0f,0.0f,//upper right
		 0.5f  , 0.0f  , 0.5f,    0.83f, 0.70f , 0.44f,    5.0f,0.0f,//lower left corner
		 0.0f  , 0.8f  , 0.0f,    0.92f,0.86f  , 0.76f,    2.5f,5.0f

	};

	GLuint indices[] = {
				0,1,2,
				0,2,3,
				0,1,4,
				1,2,4,
				2,3,4,
				3,0,4
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

	glfwSwapInterval(5);

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	

	//textures
	Texture gojo("gojo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	gojo.texunit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		//use the shader program ,bind the array,and the draw the triangle
		shaderProgram.Activate(); 


		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		gojo.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);


	}




	//cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	gojo.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}