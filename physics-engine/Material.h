#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include<glm/glm.hpp>
#include<vector>

#include"Texture.h"

class Material {
	public:
		glm::vec3 diffusecolor;
		glm::vec3 specularColor;

		float shininess;

		Texture* diffuseTexture = nullptr;
		Texture* specularTexture = nullptr;

		Material();
};



#endif // !MATERIAL_CLASS_H

