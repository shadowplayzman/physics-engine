#include "mesh.h"
#include "ShaderClass.h"
#include "PrimitiveMeshFactory.h"
#include "Universe.h"
#include "CelestialBody.h"
#include"SolarSystemFactory.h"
#include"TrailRenderer.h"
#include "Camera.h"
#include"Constants.h"
#include"SImulationState.h"


// size of the window
const GLint width = 800, height = 800;
Universe universe;
SimulationState simulationState = SimulationState::Running;


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
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

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

	// running the shaders for the trails
	Shader trailShader("trail.vert", "trail.frag");

	//creating an object to use trailRender
	TrailRenderer trailRenderer;

	//defining the color position for the lights
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightmodel = glm::mat4(1.0f);
	lightmodel = glm::translate(lightmodel, lightPos);


	//getiing the location of the uniforms for light pos and colour
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//enabled this to allow opengl to render objects with depth
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 150.0f));
	//allow us to scroll to zoom in and out
	glfwSetWindowUserPointer(window, &camera);
	glfwSetScrollCallback(window, ScrollCallback);

	//creating a mesh to render all the the spheres
	Mesh sphereMesh = PrimitiveMeshFactory::CreateSphere(1.0f, 32, 32);

	//calling the function to create the solar sytem
	SolarSystemFactory::CreateSolarSystem(universe, sphereMesh);

	size_t currentTargetIndex = 0;
	bool tabWasPressed = false;

	//allows to orbit the camera around an object in the universe class
	camera.SetTarget(universe.GetBody(currentTargetIndex));

	double lastFrame = glfwGetTime();
	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		bool tabPressed = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

		if (tabPressed && !tabWasPressed) {
			currentTargetIndex++;
			if (currentTargetIndex >= universe.BodyCount()) {
				currentTargetIndex = 0;
			}
			camera.SetTarget(universe.GetBody(currentTargetIndex));
			simulationState = SimulationState::CameraTranstion;
		}
		tabWasPressed = tabPressed;

		//calculating dt by subrating last frame from current frame
		double currentFrame = glfwGetTime();
		double dt = (currentFrame - lastFrame) * Constants::Rendering::Timescale;
		lastFrame = currentFrame;
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//updating the universe to all ohysics
		camera.Inputs(window);
		bool resumeSimulation = false;
		if (simulationState == SimulationState::CameraTranstion && !camera.IsTranstioning()) {
			resumeSimulation = true;
		}
		if (simulationState == SimulationState::Running) {
			universe.Update(dt);
		}
		if (resumeSimulation) {
			simulationState = SimulationState::Running;
		}

		//allows to control camera
		//defining the fov,near angle and far angle fot the camera
		camera.updateMatrix(90.0f, 0.1f, 100000.0f);
		shaderProgram.Activate();

		//geting each body from the universe and rendering it also rendering its trail
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