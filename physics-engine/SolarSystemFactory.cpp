#include"SolarSystemFactory.h"
#include"CelestialBody.h"
#include"Constants.h"

void SolarSystemFactory::CreateSun(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* sun = new CelestialBody(Constants::Sun::Mass, Constants::Sun::Radius);
	sun->renderable.mesh = &sphereMesh;
	sun->transform.position = glm::dvec3(0.0f);
	sun->visualScale = 25.0f;
	universe.AddBody(sun);
}

void SolarSystemFactory::CreateMercury(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* mercury = new CelestialBody(Constants::Mercury::Mass, Constants::Mercury::Radius);
	mercury->renderable.mesh = &sphereMesh;
	mercury->transform.position = glm::dvec3(Constants::Mercury::Distance, 0.0f, 0.0f);
	mercury->velocity = glm::dvec3(0.0, Constants::Mercury::OrbitalSpeed, 0.0);
	mercury->visualScale = 2000.0f;
	universe.AddBody(mercury);
}

void SolarSystemFactory::CreateVenus(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* venus = new CelestialBody(Constants::Venus::Mass, Constants::Venus::Radius);
	venus->renderable.mesh = &sphereMesh;
	venus->transform.position = glm::dvec3(Constants::Venus::Distance, 0.0f, 0.0f);
	venus->velocity = glm::dvec3(0.0, Constants::Venus::OrbitalSpeed, 0.0);
	venus->visualScale = 1600.0f;
	universe.AddBody(venus);
}

void SolarSystemFactory::CreateEarth(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* earth = new CelestialBody(Constants::Earth::Mass, Constants::Earth::Radius);
	earth->renderable.mesh = &sphereMesh;
	earth->transform.position = glm::dvec3(Constants::Earth::Distance, 0.0f, 0.0f);
	earth->velocity = glm::dvec3(0.0, Constants::Earth::OrbitalSpeed, 0.0);
	earth->visualScale = 1600.0f;
	universe.AddBody(earth);
}

void SolarSystemFactory::CreateMars(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* mars = new CelestialBody(Constants::Mars::Mass, Constants::Mars::Radius);
	mars->renderable.mesh = &sphereMesh;
	mars->transform.position = glm::dvec3(Constants::Mars::Distance, 0.0f, 0.0f);
	mars->velocity = glm::dvec3(0.0, Constants::Mars::OrbitalSpeed, 0.0);
	mars->visualScale = 1800.0f;
	universe.AddBody(mars);
}

void SolarSystemFactory::CreateJupiter(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* jupiter = new CelestialBody(Constants::Jupiter::Mass, Constants::Jupiter::Radius);
	jupiter->renderable.mesh = &sphereMesh;
	jupiter->transform.position = glm::dvec3(Constants::Jupiter::Distance, 0.0f, 0.0f);
	jupiter->velocity = glm::dvec3(0.0, Constants::Jupiter::OrbitalSpeed, 0.0);
	jupiter->visualScale = 250.0f;
	universe.AddBody(jupiter);

}
void SolarSystemFactory::CreateSaturn(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* saturn = new CelestialBody(Constants::Saturn::Mass, Constants::Saturn::Radius);
	saturn->renderable.mesh = &sphereMesh;
	saturn->transform.position = glm::dvec3(Constants::Saturn::Distance, 0.0f, 0.0f);
	saturn->velocity = glm::dvec3(0.0, Constants::Saturn::OrbitalSpeed, 0.0);
	saturn->visualScale = 300.0f;
	universe.AddBody(saturn);

}

void SolarSystemFactory::CreateUranus(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* uranus = new CelestialBody(Constants::Uranus::Mass, Constants::Uranus::Radius);
	uranus->renderable.mesh = &sphereMesh;
	uranus->transform.position = glm::dvec3(Constants::Uranus::Distance, 0.0f, 0.0f);
	uranus->velocity = glm::dvec3(0.0, Constants::Uranus::OrbitalSpeed, 0.0);
	uranus->visualScale = 450.0f;
	universe.AddBody(uranus);

}

void SolarSystemFactory::CreateNeptune(Universe& universe, Mesh& sphereMesh) {
	CelestialBody* neptune = new CelestialBody(Constants::Neptune::Mass, Constants::Neptune::Radius);
	neptune->renderable.mesh = &sphereMesh;
	neptune->transform.position = glm::dvec3(Constants::Neptune::Distance, 0.0f, 0.0f);
	neptune->velocity = glm::dvec3(0.0, Constants::Neptune::OrbitalSpeed, 0.0);
	neptune->visualScale = 450.0f;
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