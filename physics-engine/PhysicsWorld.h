#ifndef PHYSICS_CLASS_H
#define PHYSICS_CLASS_H
 
#include<vector>
#include<glm/glm.hpp>

class Rigidbody;

class PhysicsWorld {
public:
	std::vector<Rigidbody*> bodies;
	glm::vec3 gravity;
	PhysicsWorld(const glm::vec3& gravity);
	void AddBody(Rigidbody* body);
	void Update(float dt);
};

#endif // !PHYSICS_CLASS_H
