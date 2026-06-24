#ifndef SPHEREMESH_CLASS_H
#define SPHEREMESH_CLASS_H

#include"mesh.h"

class SphereMesh {
	public:
		Mesh* mesh;
		
		SphereMesh(float radius, int sectors, int stacks);
		~SphereMesh();
};



#endif // !SPHEREMESH_CLASS_H

