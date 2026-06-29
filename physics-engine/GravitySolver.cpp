#include"GravitySolver.h"
#include"CelestialBody.h"

void GravitySolver::ApplyGravity(std::vector<CelestialBody*>& bodies) {
	for (size_t i = 0;i < bodies.size();i++) {
		for (size_t j = i + 1;j < bodies.size();j++) {
			CelestialBody* bodyA = bodies[i];
			CelestialBody* bodyB = bodies[j];

			glm::vec3 displacment = bodyB->transform.position - bodyA->transform.position;
			float distance = glm::length(displacment);
			const float G = 1.0f;

			glm::vec3 direction = glm::normalize(displacment);
			if (distance == 0.0f)
				continue;
			glm::vec3 gravityForce = (G * bodyA->mass * bodyB->mass * displacment) / (distance * distance * distance);

			bodyA->AddForce(gravityForce);
			bodyB->AddForce(-gravityForce);
		}
	}
}