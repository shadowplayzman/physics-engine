#include"mesh.h"

#include"Texture.h" 
#include"Transform.h"
#include"EBO.h"
#include"PhysicsWorld.h"
#include"ShaderClass.h"
#include"Collider.h"
#include"PrimitiveMeshFactory.h"
#include"RigidBody.h"
#include"Renderable.h"
#include"VAO.h"
#include"Camera.h"
#include"VBO.h"


// size of the window
const GLint width = 800, height = 800;
PhysicsWorld world(glm::vec3(0.0f, 0.0f, 0.0f));


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

	Camera camera(width, height, glm::vec3(0.0f, 0.0f,20.0f));

	Mesh sphereMesh =PrimitiveMeshFactory::CreateSphere(1.0f, 32, 32);
	Rigidbody body(1.0f);
	Rigidbody body1(1.0f);

	

	Renderable sphere;
	sphere.mesh = &sphereMesh;
	Renderable sphere1;
	sphere1.mesh = &sphereMesh;

	SphereCollider sphereCollider(1.0f);
	body.collider = &sphereCollider;
	SphereCollider sphereCollider1(1.0f);
	body1.collider = &sphereCollider1;

	body.transform = &sphere.transform;
	world.AddBody(&body);
	body1.transform = &sphere1.transform;
	body1.transform->position = glm::vec3(4.0f, 0.f, 0.0f);
	body1.velocity= glm::vec3(4.0f, 0.f, 0.0f);
	body1.mass=5.0f;
	world.AddBody(&body1);

	float lastFrame = glfwGetTime();
	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		float currentFrame = glfwGetTime();
		float dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		world.Update(dt);
		//use the shader program ,bind the array,and the draw the triangle


		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		shaderProgram.Activate(); 
		sphere.Draw(shaderProgram, camera);
		sphere1.Draw(shaderProgram, camera);


		glfwSwapBuffers(window);


	}




	//cleanup

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}