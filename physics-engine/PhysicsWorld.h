#ifndef PHYSICS_CLASS_H
#define PHYSICS_CLASS_H
 
#include<vector>
#include"Circle.h"

class PhysicsWorld {
public:
	std::vector<Circle> balls;
	float gravity;
	PhysicsWorld(float gravityValue);
	void update(float dt);
};

#endif // !PHYSICS_CLASS_H
