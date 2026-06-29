#include"CelestialBody.h"

CelestialBody::CelestialBody(float mass) {
	this->mass = mass;
}

void CelestialBody::AddForce(const glm::vec3& force) {
	accumulatedForce += force;
}

void CelestialBody::Integrate(float dt) {
	accelration = accumulatedForce / mass;

	velocity += accelration * dt;

	transform.position += velocity * dt;

}

void CelestialBody::ClearForces() {
	accumulatedForce = glm::vec3(0.0f);
}