#ifndef RENDERABLE_CLASS_H
#define RENDERABLE_CLASS_H

#include"Transform.h"
#include"Material.h"
#include"mesh.h"
#include"ShaderClass.h"
#include"Camera.h"

class Renderable {
	public:
		Mesh* mesh = nullptr;

		Material material;
		Renderable();

		void Draw(Shader& shader, Camera& camera,const Transform& transform);
};



#endif // !RENDERABLE_CLASS_H

