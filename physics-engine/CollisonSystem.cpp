#include"CollisonSystem.h"
#include"RigidBody.h"
#include"Collider.h"
#include"Transform.h"

#include"PhysicsWorld.h"

void CollisonSystem::Solve(Rigidbody* body) {
	SphereCollider* sphere = static_cast<SphereCollider*>(body->collider);
	float groundHeight = -10.0f;

	float radius = sphere->radius;
	if (body->transform->position.y - radius < groundHeight) {
		body->transform->position.y = groundHeight + radius;
		body->velocity.y *= -0.5f;
	}
}