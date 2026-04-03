#include"Transform.h"
glm::mat4 Transform::GetMatrix() const {
	//Materices for the scale,rotation and position of object
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position));
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}