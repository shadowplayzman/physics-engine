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

	if (trailTimer >= trailSettings.trailInterval) {
		trail.push_back(transform.position);
		trailTimer -= trailSettings.trailInterval;
		while (trail.size() > trailSettings.maxStoredPoints) {
		trail.erase(trail.begin());
		}
	}

}

void CelestialBody::SetRadiusPercentage(double percentage, bool preserveDensity) {
	double scale = percentage / 100.0;
	radius = originalRadius * scale;
	if (preserveDensity) {
		mass = originalMass * scale * scale * scale;
	}
}

void CelestialBody::SetMassPercentage(double percentage) {
	double scale = percentage / 100;
	mass = originalMass * scale;
}
void CelestialBody::SetVelocity(glm::dvec3 newVelocity) {
	velocity = newVelocity;
}

void CelestialBody::ClearForces() {
	accumulatedForce = glm::dvec3(0.0f);
}