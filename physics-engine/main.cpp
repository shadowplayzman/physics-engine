#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include<vector>
#include<cmath>

#include"Texture.h" 
#include"EBO.h"
#include"Circle.h"
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"


// size of the window
const GLint width = 800, height = 800;

// velocity  and accleration

float dt = 1.0f / 60.0f;
const float gravity = -0.005f;


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
	/*GLfloat vertices[] = {
		//       cordinates								/  colors		
		-0.5f  ,-0.5f  ,0.0f,    1.0f,0.0f , 0.0f,    0.0f,0.0f,//lower left conrer
		-0.5f  , 0.5f  ,0.0f,    0.0f,1.0f , 0.0f,    0.0f,1.0f,//upper left corner
		 0.5f  , 0.5f  ,0.0f,    0.0f,0.0f , 1.0f,    1.0f,1.0f,//upper right
		 0.5f  ,-0.5f  ,0.0f,    1.0f,1.0f , 1.0f,    1.0f,0.0f,//lower left corner

	};

	GLuint indices[] = {
				0,2,1,
				0,3,2
	};*/

	const int segments = 100;
	std::vector<GLfloat> vertices;

	//center vertex
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	//color
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	 
	//texture
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);

	for (int i = 0;i <= segments;i++) {
		float angle = 2.0f * 3.14159 * i / segments;

		float x = 0.5f * cos(angle);
		float y = 0.5f * sin(angle);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(x+0.5);
		vertices.push_back(y+0.5);


	}








	// create window
	GLFWwindow* window = glfwCreateWindow(width, height, "Physics Engine", NULL, NULL);

	if (!window) {
		std::cout << "failed to create window" << "\n";
		glfwTerminate();
		return 1;
	}

	//Get frame buffer size
	int bufferwidth = 1200, bufferheight = 1200;
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
	Circle ball(0.0f, 0.0f, 0.15f);
	//bindin vao1
	VAO VAO1;
	VAO1.Bind();

	//refrencing vertices to VBO EBO
	VBO VBO1(vertices.data(), vertices.size()*sizeof(GLfloat));
	//EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	
	//gets id of unifprm called scale
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint offsetLoc = glGetUniformLocation(shaderProgram.ID, "offset");
	//textures
	Texture gojo("gojo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	gojo.texunit(shaderProgram, "tex0", 0);

	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		bool onground = (ball.y - ball.radius <= -0.65f + 0.001f);

		//use the shader program ,bind the array,and the draw the triangle
		shaderProgram.Activate();
		ball.ApplyGravity(gravity,dt);
		ball.update(dt);
		ball.checkWallCollision(-0.65f, 0.65f, 0.65f, -0.65f);
		

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			ball.vx -= 0.001f;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			ball.vx += 0.001f;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS  &&onground) {
			ball.vy = 0.05f;
		}


		glUniform2f(offsetLoc, ball.x, ball.y);
		gojo.Bind();
		VAO1.Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
		glfwSwapBuffers(window);

		

	}




	//cleanup
	VAO1.Delete();
	VBO1.Delete();
	//EBO1.Delete();
	gojo.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}