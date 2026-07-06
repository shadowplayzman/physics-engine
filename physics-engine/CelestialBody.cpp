#include"CelestialBody.h"

//gives mass and radius to the body
CelestialBody::CelestialBody(double mass,double radius) {
	this->mass = mass;
	this->radius = radius;

	originalMass = mass;
	originalRadius = radius;
}

void CelestialBody::AddForce(const glm::dvec3& force) {
	accumulatedForce += force;
}

void CelestialBody::Integrate(double dt) {



	accelration = accumulatedForce / mass;

	velocity += accelration * dt;

	transform.position += velocity * dt;

	trailTimer += dt;

	if (trailTimer >= TrailInterval) {
		trail.push_back(transform.position);
		trailTimer -= TrailInterval;
		if (trail.size() > 1500) {
		trail.erase(trail.begin());
		}
	}

}

void CelestialBody::ClearForces() {
	accumulatedForce = glm::dvec3(0.0f);
}