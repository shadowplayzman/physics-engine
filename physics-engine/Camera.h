#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#define GLM_ENABLE_EXPERIMENTAL

#include<gl/glew.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"ShaderClass.h"
class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 camMatrix = glm::mat4(1.0f);
	glm::vec3 Target = glm::vec3(0.0f);

	int width;
	int height;

	bool firstClick = true;
	float speed = 0.1f;
	float sensitivity = 100.0f;
	float Distance = 150.0f;

	float Yaw = -90.0f;
	float Pitch = 0.0f;

	Camera(int width, int height, glm::vec3 position);

	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void ProccessScroll(double offset);
	void Inputs(GLFWwindow* window);
};


#endif // !CAMERA_CLASS_H
