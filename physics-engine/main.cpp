#include "mesh.h"
#include "ShaderClass.h"
#include "PrimitiveMeshFactory.h"
#include "Universe.h"
#include "CelestialBody.h"
#include"SolarSystemFactory.h"
#include"TrailRenderer.h"
#include "Camera.h"
#include"Constants.h"
#include"SimulationState.h"
#include"SandBoxUI.h"
#include"SimulationSettings.h"
#include"SkySphere.h"
#include "imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"


// size of the window
const GLint width = 1920, height = 1080;
Universe universe;
SimulationState simulationState = SimulationState::Running;
SimulationSettings simulationsettings;




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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


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

	//creating a mesh to render all the the spheres
	Mesh sphereMesh = PrimitiveMeshFactory::CreateSphere(1.0f, 32, 32);
	Mesh saturnRingMesh = PrimitiveMeshFactory::CreateRing(1.25f, 2.35f, 128);

	//getiing the location of the uniforms for light pos and colour
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Texture sunTexture("sun.png", "diffuse", 0);
	Texture mercuryTexture("mercury.png", "diffuse", 0);
	Texture venusTexture("venus.png", "diffuse", 0);
	Texture earthTexture("earth.png", "diffuse", 0);
	Texture marsTexture("mars.png", "diffuse", 0);
	Texture jupiterTexture("jupiter.png", "diffuse", 0);
	Texture saturnTexture("saturn.png", "diffuse", 0);
	Texture uranusTexture("uranus.png", "diffuse", 0);
	Texture neptuneTexture("neptune.png", "diffuse", 0);

	PlanetTextures textures{
	sunTexture,
	mercuryTexture,
	venusTexture,
	earthTexture,
	marsTexture,
	jupiterTexture,
	saturnTexture,
	uranusTexture,
	neptuneTexture
	};

	Material saturnRingMaterial;

	Texture saturnRingTexture("saturnRing.png", "diffuse", 0);

	saturnRingMaterial.diffuseTexture = &saturnRingTexture;

	saturnRingMaterial.diffusecolor = glm::vec3(0.83f, 0.80f, 0.68f);
	saturnRingMaterial.specularColor = glm::vec3(0.1f);
	saturnRingMaterial.shininess = 4.0f;


	//enabled this to allow opengl to render objects with depth
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 150.0f));
	//allow us to scroll to zoom in and out
	glfwSetWindowUserPointer(window, &camera);
	glfwSetScrollCallback(window, ScrollCallback);

	SandBoxUI ui;

	SkySphere skysphere;

	//calling the function to create the solar sytem
	SolarSystemFactory::CreateSolarSystem(universe, sphereMesh,textures);

	size_t currentTargetIndex = 0;
	bool tabWasPressed = false;

	//allows to orbit the camera around an object in the universe class
	camera.SetTarget(universe.GetBody(currentTargetIndex));

	double lastFrame = glfwGetTime();
	//main loop

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ui.DrawSimulationWindow(simulationsettings, simulationState, universe, camera);
		ui.DrawPlanetWindow(simulationsettings,simulationState,universe,camera);
		ui.DrawPlanetSpawner(simulationsettings, simulationState,universe,camera,sphereMesh);
		//get and handle user inputs
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
		double dt = (currentFrame - lastFrame) *simulationsettings.TimeScale;
		lastFrame = currentFrame;
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skysphere.Draw(camera);

		//updating the universe to all ohysics
		camera.Inputs(window);
		bool resumeSimulation = false;
		if (simulationState == SimulationState::CameraTranstion && !camera.IsTranstioning()) {
			resumeSimulation = true;
		}
		if (!simulationsettings.paused && simulationState == SimulationState::Running) {
			universe.Update(dt);
			simulationsettings.SimulationTime += dt;
		}
		if (resumeSimulation) {
			simulationState = SimulationState::Running;
		}

		//allows to control camera
		//defining the fov,near angle and far angle fot the camera
		camera.updateMatrix(90.0f, 0.1f, 100000.0f);
		if (simulationsettings.ResetRequested) {
			universe.Clear();

			SolarSystemFactory::CreateSolarSystem(universe, sphereMesh, textures);

			currentTargetIndex = 0;
			camera.SetTarget(universe.GetBody(0));

			simulationsettings.SimulationTime = 0.0;
			simulationsettings.ResetRequested = false;
		}
		shaderProgram.Activate();

		//geting each body from the universe and rendering it also rendering its trail
		for (CelestialBody* body : universe.bodies) {
			body->renderable.Draw(shaderProgram, camera, body->transform, body->radius);
			trailRenderer.Draw(*body, trailShader, camera);

			if (body->Name == "Saturn") {
				//draw saturn ring Here
				double renderRadius = Renderable::CalculateRenderRadius(body->radius);

				Transform ringTransform;
				glm::quat tilt = glm::angleAxis(glm::radians(26.7f), glm::vec3(0.0f, 0.0f, 1.0f));

				ringTransform.position = body->transform.position/Constants::Rendering::DistanceScale;
				ringTransform.rotation = body->transform.rotation*tilt;
				ringTransform.scale = glm::vec3(renderRadius*2.2f);

				saturnRingMesh.Draw(
					shaderProgram,
					camera,
					ringTransform.GetMatrix(),
					ringTransform.position,
					ringTransform.rotation,
					ringTransform.scale,
					saturnRingMaterial);
			}
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

	}




	//cleanup

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}