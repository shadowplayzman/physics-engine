#include "mesh.h"
#include "ShaderClass.h"
#include "PrimitiveMeshFactory.h"
#include "Universe.h"
#include "CelestialBody.h"
#include "Camera.h"
#include"Constants.h"


// size of the window
const GLint width = 800, height = 800;
Universe universe;


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


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightmodel = glm::mat4(1.0f);
	lightmodel = glm::translate(lightmodel, lightPos);


	
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f,150.0f));

	Mesh sphereMesh =PrimitiveMeshFactory::CreateSphere(1.0f, 32, 32);
	
	CelestialBody sun(Constants::Astronomy::SolarMass);
	CelestialBody earth(Constants::Astronomy::EarthMass);
	CelestialBody mars(Constants::Astronomy::EarthMass * 0.05);
	CelestialBody jupiter(Constants::Astronomy::EarthMass*318);

	

	Renderable sphere;
	sun.renderable.mesh = &sphereMesh;
	earth.renderable.mesh = &sphereMesh;
	mars.renderable.mesh = &sphereMesh;
	jupiter.renderable.mesh = &sphereMesh;
	

	//positions
	sun.transform.position = glm::dvec3(0.0f);
	earth.transform.position = glm::dvec3(Constants::Astronomy::AU, 0.0f, 0.0f);
	mars.transform.position = glm::dvec3(Constants::Astronomy::AU * 0.387, 0.0f, 0.0f);
	jupiter.transform.position = glm::dvec3(Constants::Astronomy::AU*5.2, 0.0f, 0.0f);
	//velovity
	earth.velocity = glm::dvec3(0.0, Constants::Astronomy::EarthOrbitalSpeed, 0.0);
	mars.velocity = glm::dvec3(0.0, Constants::Astronomy::EarthOrbitalSpeed * 1.6, 0.0);
	jupiter.velocity = glm::dvec3(0.0, Constants::Astronomy::EarthOrbitalSpeed*0.43, 0.0);

	universe.AddBody(&sun);
	universe.AddBody(&earth);
	universe.AddBody(&mars);
	universe.AddBody(&jupiter);


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
		sun.renderable.Draw(shaderProgram, camera,sun.transform);
		earth.renderable.Draw(shaderProgram, camera, earth.transform);
		mars.renderable.Draw(shaderProgram, camera, mars.transform);
		jupiter.renderable.Draw(shaderProgram, camera,jupiter.transform);

		glfwSwapBuffers(window);

	}




	//cleanup

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}