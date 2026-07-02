#ifndef TRAIL_RENDERER_H
#define TRAIL_RENDERER_H

#include <vector>
#include"ShaderClass.h"
#include"Camera.h"
#include"VAO.h"
#include"VBO.h"

class CelestialBody;

class TrailRenderer {
	public:
		TrailRenderer();

		void Draw(const CelestialBody& body, Shader& shader, Camera& camera);

	private:
		VAO vao;
		VBO vbo;
};


#endif // !TRAIL_RENDERER_H

