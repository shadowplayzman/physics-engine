#include"Material.h"

Material::Material() {
	diffusecolor = glm::vec3(1.0f);
	specularColor = glm::vec3(1.0f);

	shininess = 32.0f;

	diffuseTexture = nullptr;
	specularTexture = nullptr;
}