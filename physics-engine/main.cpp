#include "mesh.h"
#include "ShaderClass.h"
#include "PrimitiveMeshFactory.h"
#include "Universe.h"
#include "CelestialBody.h"
#include"SolarSystemFactory.h"
#include"TrailRenderer.h"
#include "Camera.h"
#include"Constants.h"


// size of the window
const GLint width = 800, height = 800;
Universe universe;

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	camera->ProccessScroll(yoffset);
}

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

	glfwSwapInterval(1);

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
	Shader shaderProgram("default.vert", "default.frag");;

	Shader lightShader("light.vert", "light.frag");
	Shader trailShader("trail.vert", "trail.frag");

	TrailRenderer trailRenderer;


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightmodel = glm::mat4(1.0f);
	lightmodel = glm::translate(lightmodel, lightPos);


	
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f,150.0f));
	glfwSetWindowUserPointer(window, &camera);
	glfwSetScrollCallback(window, ScrollCallback);

	Mesh sphereMesh =PrimitiveMeshFactory::CreateSphere(1.0f, 32, 32);
	

	

	//positions
	//velovity




	SolarSystemFactory::CreateSolarSystem(universe, sphereMesh);

	double lastFrame = glfwGetTime();
	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		double currentFrame = glfwGetTime();
		double dt = (currentFrame - lastFrame)*Constants::Rendering::Timescale;
		lastFrame = currentFrame;
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		universe.Update(dt);
		//use the shader program ,bind the array,and the draw the triangle

		camera.Inputs(window);
		camera.updateMatrix(90.0f, 0.1f, 100000.0f);
		shaderProgram.Activate(); 

		for (CelestialBody* body : universe.bodies) {
			body->renderable.Draw(shaderProgram, camera, body->transform, body->radius, body->visualScale);
			trailRenderer.Draw(*body, trailShader, camera);
		}

		glfwSwapBuffers(window);

	}




	//cleanup

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}