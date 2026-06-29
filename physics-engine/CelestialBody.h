#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include<glm/glm.hpp>
#include"Transform.h"
#include"Renderable.h"

class CelestialBody {
public:
	Transform transform ;
	Renderable renderable;


	float mass;

	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 accelration = glm::vec3(0.0f);
	glm::vec3 accumulatedForce = glm::vec3(0.0f);

	CelestialBody(float mass = 1.0f);

	void AddForce(const glm::vec3& force);

	void Integrate(float dt);

	void ClearForces();
};



#endif
