#ifndef TRANSFORM_CLASS_H
#define TRANSFORM_CLASS_H

#define GLM_ENABLE_EXPERIMENTAL

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/quaternion.hpp>

struct Transform
{
	glm::vec3 position = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	glm::mat4 GetMatrix() const;
};


#endif // !TRANSFORM_CLASS_H

