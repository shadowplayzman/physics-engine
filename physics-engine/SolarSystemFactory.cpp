#include"SolarSystemFactory.h"
#include"CelestialBody.h"
#include"Constants.h"

void SolarSystemFactory::CreateSun(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* sun = new CelestialBody(Constants::Sun::Mass, Constants::Sun::Radius);
	sun->renderable.mesh = &sphereMesh;
	sun->transform.position = glm::dvec3(0.0f);
	sun->visualScale = 25.0f;
	sun->mass = Constants::Sun::Mass;
	sun->radius = Constants::Sun::Radius;
	sun->originalMass = sun->mass;
	sun->originalRadius = sun->radius;
	sun->Name = "Sun";
	universe.AddBody(sun);
}

void SolarSystemFactory::CreateMercury(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* mercury = new CelestialBody(Constants::Mercury::Mass, Constants::Mercury::Radius);
	mercury->renderable.mesh = &sphereMesh;
	mercury->transform.position = glm::dvec3(Constants::Mercury::Distance, 0.0f, 0.0f);
	mercury->velocity = glm::dvec3(0.0, Constants::Mercury::OrbitalSpeed, 0.0);
	mercury->visualScale = 2000.0f;
	mercury->mass = Constants::Mercury::Mass;
	mercury->radius = Constants::Mercury::Radius;
	mercury->originalMass = mercury->mass;
	mercury->originalRadius = mercury->radius;
	mercury->Name = "Mercury";
	universe.AddBody(mercury);
}

void SolarSystemFactory::CreateVenus(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* venus = new CelestialBody(Constants::Venus::Mass, Constants::Venus::Radius);
	venus->renderable.mesh = &sphereMesh;
	venus->transform.position = glm::dvec3(Constants::Venus::Distance, 0.0f, 0.0f);
	venus->velocity = glm::dvec3(0.0, Constants::Venus::OrbitalSpeed, 0.0);
	venus->visualScale = 1600.0f;
	venus->mass = Constants::Venus::Mass;
	venus->radius = Constants::Venus::Radius;
	venus->originalMass = venus->mass;
	venus->originalRadius = venus->radius;
	venus->Name = "Venus";
	universe.AddBody(venus);
}

void SolarSystemFactory::CreateEarth(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* earth = new CelestialBody(Constants::Earth::Mass, Constants::Earth::Radius);
	earth->renderable.mesh = &sphereMesh;
	earth->transform.position = glm::dvec3(Constants::Earth::Distance, 0.0f, 0.0f);
	earth->velocity = glm::dvec3(0.0, Constants::Earth::OrbitalSpeed, 0.0);
	earth->visualScale = 1600.0f;
	earth->mass = Constants::Earth::Mass;
	earth->radius = Constants::Earth::Radius;
	earth->originalMass = earth->mass;
	earth->originalRadius = earth->radius;
	earth->Name = "Earth";
	universe.AddBody(earth);
}

void SolarSystemFactory::CreateMars(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* mars = new CelestialBody(Constants::Mars::Mass, Constants::Mars::Radius);
	mars->renderable.mesh = &sphereMesh;
	mars->transform.position = glm::dvec3(Constants::Mars::Distance, 0.0f, 0.0f);
	mars->velocity = glm::dvec3(0.0, Constants::Mars::OrbitalSpeed, 0.0);
	mars->visualScale = 1800.0f;
	mars->mass = Constants::Mars::Mass;
	mars->radius = Constants::Mars::Radius;
	mars->originalMass = mars->mass;
	mars->originalRadius = mars->radius;
	mars->Name = "Mars";
	universe.AddBody(mars);
}

void SolarSystemFactory::CreateJupiter(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* jupiter = new CelestialBody(Constants::Jupiter::Mass, Constants::Jupiter::Radius);
	jupiter->renderable.mesh = &sphereMesh;
	jupiter->transform.position = glm::dvec3(Constants::Jupiter::Distance, 0.0f, 0.0f);
	jupiter->velocity = glm::dvec3(0.0, Constants::Jupiter::OrbitalSpeed, 0.0);
	jupiter->visualScale = 250.0f;
	jupiter->mass = Constants::Jupiter::Mass;
	jupiter->radius = Constants::Jupiter::Radius;
	jupiter->originalMass = jupiter->mass;
	jupiter->originalRadius = jupiter->radius;
	jupiter->Name = "Jupiter";
	universe.AddBody(jupiter);

}
void SolarSystemFactory::CreateSaturn(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* saturn = new CelestialBody(Constants::Saturn::Mass, Constants::Saturn::Radius);
	saturn->renderable.mesh = &sphereMesh;
	saturn->transform.position = glm::dvec3(Constants::Saturn::Distance, 0.0f, 0.0f);
	saturn->velocity = glm::dvec3(0.0, Constants::Saturn::OrbitalSpeed, 0.0);
	saturn->visualScale = 300.0f;
	saturn->mass = Constants::Saturn::Mass;
	saturn->radius = Constants::Saturn::Radius;
	saturn->originalMass = saturn->mass;
	saturn->originalRadius = saturn->radius;
	saturn->Name = "Saturn";
	universe.AddBody(saturn);

}

void SolarSystemFactory::CreateUranus(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* uranus = new CelestialBody(Constants::Uranus::Mass, Constants::Uranus::Radius);
	uranus->renderable.mesh = &sphereMesh;
	uranus->transform.position = glm::dvec3(Constants::Uranus::Distance, 0.0f, 0.0f);
	uranus->velocity = glm::dvec3(0.0, Constants::Uranus::OrbitalSpeed, 0.0);
	uranus->visualScale = 450.0f;
	uranus->mass = Constants::Uranus::Mass;
	uranus->radius = Constants::Uranus::Radius;
	uranus->originalMass = uranus->mass;
	uranus->originalRadius = uranus->radius;
	uranus->Name = "Uranus";
	universe.AddBody(uranus);

}

void SolarSystemFactory::CreateNeptune(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* neptune = new CelestialBody(Constants::Neptune::Mass, Constants::Neptune::Radius);
	neptune->renderable.mesh = &sphereMesh;
	neptune->transform.position = glm::dvec3(Constants::Neptune::Distance, 0.0f, 0.0f);
	neptune->velocity = glm::dvec3(0.0, Constants::Neptune::OrbitalSpeed, 0.0);
	neptune->visualScale = 450.0f;
	neptune->mass = Constants::Neptune::Mass;
	neptune->radius = Constants::Neptune::Radius;
	neptune->originalMass = neptune->mass;
	neptune->originalRadius = neptune->radius;
	neptune->Name = "Neptune";
	universe.AddBody(neptune);

}



void SolarSystemFactory::CreateSolarSystem(Universe& universe, Mesh& sphereMesh) {
	CreateSun(universe, sphereMesh);
	CreateMercury(universe, sphereMesh);
	CreateVenus(universe, sphereMesh);
	CreateEarth(universe, sphereMesh);
	CreateMars(universe, sphereMesh);
	CreateJupiter(universe, sphereMesh);
	CreateSaturn(universe, sphereMesh);
	CreateUranus(universe, sphereMesh);
	CreateNeptune(universe,sphereMesh);
}	