#include"Camera.h"
#include"CelestialBody.h"
#include"Constants.h"
#include"Universe.h"

//to give camera the data for the height and width of the window
Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

//updates the matrix 
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	view = glm::lookAt(Position , Target, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);
	camMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}
//allows us to zoom in and out the camera
void Camera::ProccessScroll(double offset) {
	constexpr float MinZoom = 5.0f;
	constexpr float MaxZoom = 5000.0f;

	Distance -= offset *Distance* 0.1f;
	Distance = glm::clamp(Distance, MinZoom, MaxZoom);
}
//we can set target to which we want to revolve our camera around
void Camera::SetTarget(CelestialBody* body) {
	targetBody = body;
	DesiredTarget = glm::vec3(body->transform.position / Constants::Rendering::DistanceScale);
}
//takes all the inputs for the camera like moving,scrolling,etc
void Camera::Inputs(GLFWwindow* window) {
	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation,Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}	
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed=0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}*/
	if (targetBody != nullptr) {
		DesiredTarget = glm::vec3(targetBody->transform.position / Constants::Rendering::DistanceScale);
		Target = glm::mix(Target, DesiredTarget, 0.02f);
		Position = Target - Orientation * Distance;
	}
	//checks if it its the first click if yes it resets the camera back to orgin 
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		double mousex, mousey;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClick == true) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}
		glfwGetCursorPos(window, &mousex, &mousey);

		float rotx = sensitivity * (float)(mousey - (height / 2)) / height;
		float roty = sensitivity * (float)(mousex - (width / 2)) / height;

		Pitch -= rotx;
		Yaw -= roty;
		
		Pitch = glm::clamp(Pitch, -89.0f, 89.0f);

		glm::vec3 direction;
		direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		direction.y = sin(glm::radians(Pitch));
		direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		Orientation = glm::normalize(direction);
		Position = Target - Orientation * Distance;

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

}