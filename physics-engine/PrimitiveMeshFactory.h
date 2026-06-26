#ifndef PRIMITIVE_MESH_FACTORY_H
#define PRIMITIVE_MESH_FACTORY_H

#include"mesh.h"

class PrimitiveMeshFactory {
	public:
		static Mesh CreateSphere(float radius, int sectors, int stacks);
		static Mesh CreateCube(float size);
		static Mesh CreatePlane(float width, float depth);
		static Mesh CreateCylinder(float radius, float height, int sectors);
		static Mesh CreateCapsule(float radius, float height, int sectors, int stacks);
};

#endif // !PRIMITIVE_MESH_FACTORY_H

