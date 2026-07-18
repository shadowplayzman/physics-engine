#ifndef SKY_SPHERE_H
#define SKY_SPHERE_H

#include"mesh.h"
#include"Texture.h"
#include"Material.h"
#include"ShaderClass.h"
#include"Camera.h"


class SkySphere {
	public:
		SkySphere();

		void Draw(Camera& camera);

	private:
		Mesh mesh;
		Texture texture;
		Material material;
		Shader shader;
};



#endif // !SKY_SPHERE_H

