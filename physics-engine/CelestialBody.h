#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include<vector>

#include<glm/glm.hpp>
#include"Transform.h"
#include"Renderable.h"

struct TrailSettings
{
	bool visible = true;

	int maxStoredPoints = 5000;
	int displayedPoints = 300;
	double trailInterval = 3600.0;

	glm::vec3 color = glm::vec3(1.0f);

	float width = 1.0f;
};
class CelestialBody {
public:
	Transform transform ;
	Renderable renderable;
	TrailSettings trailSettings;

	std::string Name;

	double mass;
	double radius;

	double originalMass;
	double originalRadius;

	double visualScale = 1.0f;
	double trailTimer = 0.0;

	glm::dvec3 position;
	glm::dvec3 velocity = glm::dvec3(0.0f);
	glm::dvec3 accelration = glm::dvec3(0.0f);
	glm::dvec3 accumulatedForce = glm::dvec3(0.0f);

	std::vector<glm::dvec3> trail;

	CelestialBody(double mass = 1.0f,double radius=1.0f);

	void AddForce(const glm::dvec3& force);

	void Integrate(double dt);

	void SetRadiusPercentage(double percentage, bool preserveDensity);
	void SetMassPercentage(double percentage);
	void SetVelocity(glm::dvec3 newVelocity);

	void ClearForces();
};



#endif
