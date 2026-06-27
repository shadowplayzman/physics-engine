#include"PhysicsWorld.h"
#include"RigidBody.h"


PhysicsWorld::PhysicsWorld(const glm::vec3& gravity) {
	this->gravity = gravity;
}

void PhysicsWorld::Update(float dt) {
	for (Rigidbody* body : bodies) {
		if (body->useGravity) {
			body->AddForce(gravity * body->mass);
		}
	}
	for (Rigidbody* body : bodies) {
		body->Integrate(dt);
	}
	for (Rigidbody* body : bodies) {
		body->ClearForces();
	}
}

void PhysicsWorld::AddBody(Rigidbody* body) {
	bodies.push_back(body);
}