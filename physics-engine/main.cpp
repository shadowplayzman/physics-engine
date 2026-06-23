#include"mesh.h"

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
	Vertex vertices[] = {
	//               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
		Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
	};

	GLuint indices[] = {
			0, 1, 2, // Bottom side
			0, 2, 3, // Bottom side
	};

	Vertex lightVertices[] = {
			Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
			Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
			Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
			Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
			Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
			Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
			Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
			Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
	};

	GLuint lightIndices[] = {
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7
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

	Texture textures[]{
		Texture("gojo.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("gojospec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)

	};

	//running the shaderprogram function
	Shader shaderProgram("default.vert", "default.frag");
	
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices+ sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verts, ind, tex);

	Shader lightShader("light.vert", "light.frag");
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightmodel = glm::mat4(1.0f);
	lightmodel = glm::translate(lightmodel, lightPos);

	glm::vec3 pyramidpos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidmodel = glm::mat4(1.0f);
	pyramidmodel = glm::translate(pyramidmodel, pyramidpos);

	lightShader.Activate();
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"),1, GL_FALSE, glm::value_ptr(lightmodel));
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidmodel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	

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

		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		glfwSwapBuffers(window);


	}




	//cleanup

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}