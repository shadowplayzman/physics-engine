#include"RigidBody.h"
#include"Transform.h"

Rigidbody::Rigidbody(float bodymass) {
	mass = bodymass;

	if (mass <= 0.0f) {
		inverseMass = 0.0f;
	}
	else {
		inverseMass = 1.0f / mass;
	}

	velocity = glm::vec3(0.0f);
	accumulatedForce = glm::vec3(0.0f);

	useGravity = true;
}
void Rigidbody::AddForce(const glm::vec3& force) {
	accumulatedForce += force;
}
void Rigidbody::ClearForces() {
	accumulatedForce = glm::vec3(0.0f);
}
void Rigidbody::Integrate(float dt) {
	if (transform == nullptr) {
		return;
	}
	glm::vec3 acceleration = accumulatedForce * inverseMass;
	velocity += acceleration * dt;
	transform->position += velocity * dt;
}