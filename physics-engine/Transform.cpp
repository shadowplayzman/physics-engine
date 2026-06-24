#include"Transform.h"
glm::mat4 Transform::GetMatrix() const {
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}