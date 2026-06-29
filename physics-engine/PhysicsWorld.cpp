#include"PhysicsWorld.h"
#include"RigidBody.h"
#include"Collider.h"
#include"Transform.h"
#include"CollisonSystem.h"


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
		CollisonSystem::Solve(body);
	}
	for (Rigidbody* body : bodies) {
		body->ClearForces();
	}
}

void PhysicsWorld::AddBody(Rigidbody* body) {
	bodies.push_back(body);
}