#include"CelestialBody.h"

CelestialBody::CelestialBody(double mass,double radius) {
	this->mass = mass;
	this->radius = radius;
}

void CelestialBody::AddForce(const glm::dvec3& force) {
	accumulatedForce += force;
}

void CelestialBody::Integrate(double dt) {
	accelration = accumulatedForce / mass;

	velocity += accelration * dt;

	transform.position += velocity * dt;

}

void CelestialBody::ClearForces() {
	accumulatedForce = glm::dvec3(0.0f);
}