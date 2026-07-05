#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include<vector>

#include<glm/glm.hpp>
#include"Transform.h"
#include"Renderable.h"

class CelestialBody {
public:
	Transform transform ;
	Renderable renderable;

	std::string Name;

	double mass;
	double radius;
	double visualScale = 1.0f;
	double trailTimer = 0.0;

	constexpr static double TrailInterval = 3600.0;


	glm::dvec3 position;
	glm::dvec3 velocity = glm::dvec3(0.0f);
	glm::dvec3 accelration = glm::dvec3(0.0f);
	glm::dvec3 accumulatedForce = glm::dvec3(0.0f);

	std::vector<glm::dvec3> trail;

	CelestialBody(double mass = 1.0f,double radius=1.0f);

	void AddForce(const glm::dvec3& force);

	void Integrate(double dt);

	void ClearForces();
};



#endif
