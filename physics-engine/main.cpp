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
const float gravity = -9.8f;
float floorfriction = 0.4f;
std::vector<Circle> balls;

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

		float x =cos(angle);
		float y = sin(angle);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back((x + 1.0f) * 0.5f);
		vertices.push_back((y + 1.0f) * 0.5f);


	}


	balls.push_back(Circle(0.0f, 0.0f, 0.055f));
	balls.push_back(Circle(0.3f, 0.3f, 0.045f));
	balls.push_back(Circle(-0.3f, -1.0f, 0.085f));

	balls[0].vx = 0.8f;
	balls[1].vx = -0.8f;
	balls[2].vx = 0.0f;




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
	VBO VBO1(vertices.data(), vertices.size()*sizeof(GLfloat));
	//EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	
	//gets id of unifprm called scale
	GLuint scaleLoc = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint offsetLoc = glGetUniformLocation(shaderProgram.ID, "offset");
	//textures
	Texture gojo("gojo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	gojo.texunit(shaderProgram, "tex0", 0);

	float lastFrame = glfwGetTime();

	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		float dt = currentFrame - lastFrame;
		lastFrame = currentFrame;


		bool onground = (balls[0].y - balls[0].radius <= -1.0f + 0.001f);

		//use the shader program ,bind the array,and the draw the triangle
		shaderProgram.Activate();
		for (Circle& ball : balls) {
			ball.ApplyGravity(gravity, dt);
			if (onground == true) {
				float friction = floorfriction * fabs(gravity);

				if (ball.vx > 0) {
					ball.vx -= friction * dt;
					if (ball.vx == 0) {
						ball.vx = 0;
					}
				}
				if (ball.vy > 0) {
					ball.vy -= friction * dt;
					if (ball.vy == 0) {
						ball.vy = 0;
					}
				}
			}

			ball.update(dt);
			ball.checkWallCollision(-1.0f, 1.0f, 1.0f, -1.0f);

		}

		for (int i = 0;i < balls.size() ; i++) {
			for (int j = i + 1;j < balls.size(); j++) {

				Circle& A = balls[i];
				Circle& B = balls[j];

				float dx = B.x - A.x;
				float dy = B.y - A.y;


				float distance = sqrt(dx * dx + dy * dy);


				if (distance < A.radius + B.radius&&distance>0.00001f) {
					float overlap = (A.radius + B.radius) - distance;
					float nx = dx / distance;
					float ny = dy / distance;
					float totalMass = A.mass + B.mass;
	
					float rvx = A.vx - B.vx;
					float rvy = A.vy - B.vy;

					float velAlongNormal = rvx * nx + rvy * ny;


					A.x -= nx * overlap * (B.mass/totalMass);
					A.y -= ny * overlap * (B.mass / totalMass);

					B.x += nx * overlap * (B.mass / totalMass);
					B.y += ny * overlap * (B.mass / totalMass);

					if (velAlongNormal < 0) {
						float e = 0.8f;

						float j = -(1.0f + e) * velAlongNormal;

						j /= (1 / A.mass) + (1 / B.mass);

						float impluseX = j * nx;
						float impluseY = j * ny;

						A.vx -= impluseX / A.mass;
						A.vy -= impluseY / A.mass;

						B.vx -= impluseX / B.mass;
						B.vy -= impluseY / B.mass;
					}
					
				}
			}
		}
		

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			balls[0].vx -= 0.001f;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			balls[0].vx += 0.001f;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS  &&onground) {
			balls[0].vy = 0.05f;
		}


		gojo.Bind();
		VAO1.Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		for (Circle& ball : balls) {
			glUniform1f(scaleLoc, ball.radius);
			glUniform2f(offsetLoc, ball.x, ball.y);
			glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
		}
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