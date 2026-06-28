#include"PhysicsWorld.h"
#include"RigidBody.h"
#include"Collider.h"
#include"Transform.h"


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
		SphereCollider* sphere = static_cast<SphereCollider*>(body->collider);

		float radius = sphere->radius;
		if (body->transform->position.y - radius < groundHeight) {
			body->transform->position.y = groundHeight + radius;
			body->velocity.y *= -0.5f;
		}
	}
	for (Rigidbody* body : bodies) {
		body->ClearForces();
	}
}

void PhysicsWorld::AddBody(Rigidbody* body) {
	bodies.push_back(body);
}