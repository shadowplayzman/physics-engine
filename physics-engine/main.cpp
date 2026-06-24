#include"mesh.h"
#include"Model.h"

#include"Texture.h" 
#include"EBO.h"
#include"Circle.h"
#include"PhysicsWorld.h"
#include"ShaderClass.h"
#include"VAO.h"
#include"Camera.h"
#include"VBO.h"


// size of the window
const GLint width = 800, height = 800;

// velocity  and accleration
const float gravity = -9.8f;

PhysicsWorld world(gravity);

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


	world.balls.push_back(Circle(0.0f, 1.0f, 0.055f));
	world.balls.push_back(Circle(0.3f,1.0f, 0.045f));
	world.balls.push_back(Circle(-0.3f, 1.0f, 0.085f));

	world.balls[0].vx = 0.0f;
	world.balls[1].vx = -0.0f;
	world.balls[2].vx = 0.0f;




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

	

	float lastFrame = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 4.0f));

	Model model("models/sword/scene.gltf");
	

	//main loop

	while (!glfwWindowShouldClose(window)) {
		//get and handle user inputs
		glfwPollEvents();
		//clear buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		float currentFrame = glfwGetTime();
		float dt = currentFrame - lastFrame;
		lastFrame = currentFrame;


		bool onground = (world.balls[0].y - world.balls[0].radius <= -1.0f + 0.001f);

		//use the shader program ,bind the array,and the draw the triangle
		shaderProgram.Activate();

		world.update(dt);

		

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			world.balls[0].vx -= 0.1f;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			world.balls[0].vx += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS  &&onground) {
			world.balls[0].vy = 0.2f;
		}

		shaderProgram.Activate(); 

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram,camera);
		glfwSwapBuffers(window);


	}




	//cleanup

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}