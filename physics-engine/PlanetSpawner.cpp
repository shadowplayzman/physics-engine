#include"PlanetSpawer.h"
#include"Constants.h"
#include"Universe.h"
#include"CelestialBody.h"
#include"mesh.h"
void PlanetSpawner::loadTemplate() {
	switch (SelectedTemplate) {
	case Template::Sun:
		name = "Sun";
		radius = Constants::Sun::Radius;
		mass = Constants::Sun::Mass;

		position = glm::dvec3(0.0, 0.0, 0.0);
		velocity = glm::dvec3(0.0, 0.0, 0.0);
		trailColor = glm::vec3(1.00f, 0.85f, 0.20f);

		preserveDensity = true;

		break;
	case Template::Mercury:
		name = "Mercury";
		radius = Constants::Mercury::Radius;
		mass = Constants::Mercury::Mass;

		position = glm::dvec3(Constants::Mercury::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Mercury::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.65f, 0.65f, 0.65f);

		preserveDensity = true;

		break;
	case Template::Venus:
		name = "Venus";
		radius = Constants::Venus::Radius;
		mass = Constants::Venus::Mass;

		position = glm::dvec3(Constants::Venus::Distance,0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Venus::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.95f, 0.82f, 0.45f);

		preserveDensity = true;

		break;
	case Template::Earth:
		name = "Earth";
		radius = Constants::Earth::Radius;
		mass = Constants::Earth::Mass;

		position = glm::dvec3(Constants::Earth::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Earth::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.20f, 0.5f, 1.00f);

		preserveDensity = true;

		break;
	case Template::Mars:
		name = "Mars";
		radius = Constants::Mars::Radius;
		mass = Constants::Mars::Mass;

		position = glm::dvec3(Constants::Mars::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Mars::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.85f, 0.25f, 0.20f);

		preserveDensity = true;

		break;
	case Template::Jupiter:
		name = "Jupiter";
		radius = Constants::Jupiter::Radius;
		mass = Constants::Jupiter::Mass;

		position = glm::dvec3(Constants::Jupiter::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Jupiter::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.85f, 0.60f, 0.35f);

		preserveDensity = true;

		break;
	case Template::Saturn:
		name = "Saturn";
		radius = Constants::Saturn::Radius;
		mass = Constants::Saturn::Mass;

		position = glm::dvec3(Constants::Saturn::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Saturn::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.90f, 0.80f, 0.50f);

		preserveDensity = true;

		break;
	case Template::Uranus:
		name = "Uranus";
		radius = Constants::Uranus::Radius;
		mass = Constants::Uranus::Mass;

		position = glm::dvec3(Constants::Uranus::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Uranus::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.45f, 0.90f, 1.00f);

		preserveDensity = true;

		break;
	case Template::Neptune:
		name = "Neptune";
		radius = Constants::Neptune::Radius;
		mass = Constants::Neptune::Mass;

		position = glm::dvec3(Constants::Neptune::Distance, 0.0, 0.0);
		velocity = glm::dvec3(0.0, Constants::Neptune::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.20f, 0.35f, 1.00f);

		preserveDensity = true;

		break;
	case Template::Custom:
		name = "Name";
		radius = 0.0;
		mass = 0.0;

		position = glm::dvec3(0.0, 0.0, 0.0);
		velocity = glm::dvec3(0.0,0.0, 0.0);
		trailColor = glm::vec3(0.20f, 0.35f, 1.00f);

		preserveDensity = true;

		break;

	default:
		break;
}
}
void PlanetSpawner::Spawn(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* body = new CelestialBody(mass, radius);

	body->Name = name;

	body->mass = mass;
	body->radius = radius;

	body->originalMass = mass;
	body->originalRadius = radius;

	body->transform.position = position;
	body->velocity = velocity;

	body->trailSettings.color = trailColor;

	body->renderable.mesh = &sphereMesh;

	universe.AddBody(body);
}