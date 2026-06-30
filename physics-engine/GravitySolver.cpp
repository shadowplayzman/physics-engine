#include"GravitySolver.h"
#include"CelestialBody.h"
#include"Constants.h"

void GravitySolver::ApplyGravity(std::vector<CelestialBody*>& bodies) {
	for (size_t i = 0;i < bodies.size();i++) {
		for (size_t j = i + 1;j < bodies.size();j++) {
			CelestialBody* bodyA = bodies[i];
			CelestialBody* bodyB = bodies[j];

			glm::dvec3 displacment = bodyB->transform.position - bodyA->transform.position;
			double distance = glm::length(displacment);
			const double G = Constants::G;

			glm::dvec3 direction = glm::normalize(displacment);
			if (distance == 0.0)
				continue;
			glm::dvec3 gravityForce = (G * bodyA->mass * bodyB->mass * displacment) / (distance * distance * distance);

			bodyA->AddForce(gravityForce);
			bodyB->AddForce(-gravityForce);
		}
	}
}