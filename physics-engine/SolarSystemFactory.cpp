#include"SolarSystemFactory.h"
#include"CelestialBody.h"
#include"Constants.h"


void SolarSystemFactory::CreateSun(Universe& universe, Mesh& sphereMesh, Texture& sunTexture) {
	CelestialBody* sun = new CelestialBody(Constants::Sun::Mass, Constants::Sun::Radius);
	sun->renderable.mesh = &sphereMesh;
	sun->renderable.material.diffuseTexture = &sunTexture;
	sun->transform.position = glm::dvec3(0.0f);
	sun->trailSettings.color = glm::vec3(1.00f, 0.85f, 0.20f);
	sun->mass = Constants::Sun::Mass;
	sun->radius = Constants::Sun::Radius;
	sun->originalMass = sun->mass;
	sun->originalRadius = sun->radius;
	sun->renderable.material.emissive = true;
	sun->renderable.material.emissionStrength = 2.0f;
	sun->Name = "Sun";
	universe.AddBody(sun);
}

void SolarSystemFactory::CreateMercury(Universe& universe, Mesh& sphereMesh, Texture& mercuryTexture) {
	CelestialBody* mercury = new CelestialBody(Constants::Mercury::Mass, Constants::Mercury::Radius);
	mercury->renderable.mesh = &sphereMesh;
	mercury->renderable.material.diffuseTexture = &mercuryTexture;
	mercury->transform.position = glm::dvec3(Constants::Mercury::Distance, 0.0f, 0.0f);
	mercury->velocity = glm::dvec3(0.0, Constants::Mercury::OrbitalSpeed, 0.0);
	mercury->trailSettings.color = glm::vec3(0.65f, 0.65f, 0.65f);
	mercury->mass = Constants::Mercury::Mass;
	mercury->radius = Constants::Mercury::Radius;
	mercury->originalMass = mercury->mass;
	mercury->originalRadius = mercury->radius;
	mercury->Name = "Mercury";
	universe.AddBody(mercury);
}

void SolarSystemFactory::CreateVenus(Universe& universe, Mesh& sphereMesh, Texture& venusTexture) {
	CelestialBody* venus = new CelestialBody(Constants::Venus::Mass, Constants::Venus::Radius);
	venus->renderable.mesh = &sphereMesh;
	venus->renderable.material.diffuseTexture = &venusTexture;
	venus->transform.position = glm::dvec3(Constants::Venus::Distance, 0.0f, 0.0f);
	venus->velocity = glm::dvec3(0.0, Constants::Venus::OrbitalSpeed, 0.0);
	venus->trailSettings.color = glm::vec3(0.95f, 0.82f, 0.45f);
	venus->mass = Constants::Venus::Mass;
	venus->radius = Constants::Venus::Radius;
	venus->originalMass = venus->mass;
	venus->originalRadius = venus->radius;
	venus->Name = "Venus";
	universe.AddBody(venus);
}

void SolarSystemFactory::CreateEarth(Universe& universe, Mesh& sphereMesh, Texture& earthTexture) {
	CelestialBody* earth = new CelestialBody(Constants::Earth::Mass, Constants::Earth::Radius);
	earth->renderable.mesh = &sphereMesh;
	earth->renderable.material.diffuseTexture = &earthTexture;
	earth->transform.position = glm::dvec3(Constants::Earth::Distance, 0.0f, 0.0f);
	earth->velocity = glm::dvec3(0.0, Constants::Earth::OrbitalSpeed, 0.0);
	earth->trailSettings.color = glm::vec3(0.20f, 0.50f, 1.00f);
	earth->mass = Constants::Earth::Mass;
	earth->radius = Constants::Earth::Radius;
	earth->originalMass = earth->mass;
	earth->originalRadius = earth->radius;
	earth->Name = "Earth";
	universe.AddBody(earth);
}

void SolarSystemFactory::CreateMars(Universe& universe, Mesh& sphereMesh, Texture& marsTexture) {
	CelestialBody* mars = new CelestialBody(Constants::Mars::Mass, Constants::Mars::Radius);
	mars->renderable.mesh = &sphereMesh;
	mars->renderable.material.diffuseTexture = &marsTexture;
	mars->transform.position = glm::dvec3(Constants::Mars::Distance, 0.0f, 0.0f);
	mars->velocity = glm::dvec3(0.0, Constants::Mars::OrbitalSpeed, 0.0);
	mars->trailSettings.color = glm::vec3(0.85f, 0.25f, 0.20f);
	mars->mass = Constants::Mars::Mass;
	mars->radius = Constants::Mars::Radius;
	mars->originalMass = mars->mass;
	mars->originalRadius = mars->radius;
	mars->Name = "Mars";
	universe.AddBody(mars);
}

void SolarSystemFactory::CreateJupiter(Universe& universe, Mesh& sphereMesh, Texture& jupiterTexture) {
	CelestialBody* jupiter = new CelestialBody(Constants::Jupiter::Mass, Constants::Jupiter::Radius);
	jupiter->renderable.mesh = &sphereMesh;
	jupiter->renderable.material.diffuseTexture = &jupiterTexture;
	jupiter->transform.position = glm::dvec3(Constants::Jupiter::Distance, 0.0f, 0.0f);
	jupiter->velocity = glm::dvec3(0.0, Constants::Jupiter::OrbitalSpeed, 0.0);
	jupiter->trailSettings.color = glm::vec3(0.85f, 0.60f, 0.35f);
	jupiter->mass = Constants::Jupiter::Mass;
	jupiter->radius = Constants::Jupiter::Radius;
	jupiter->originalMass = jupiter->mass;
	jupiter->originalRadius = jupiter->radius;
	jupiter->Name = "Jupiter";
	universe.AddBody(jupiter);

}
void SolarSystemFactory::CreateSaturn(Universe& universe, Mesh& sphereMesh, Texture& saturnTexture) {
	CelestialBody* saturn = new CelestialBody(Constants::Saturn::Mass, Constants::Saturn::Radius);
	saturn->renderable.mesh = &sphereMesh;
	saturn->renderable.material.diffuseTexture = &saturnTexture;
	saturn->transform.position = glm::dvec3(Constants::Saturn::Distance, 0.0f, 0.0f);
	saturn->velocity = glm::dvec3(0.0, Constants::Saturn::OrbitalSpeed, 0.0);
	saturn->trailSettings.color = glm::vec3(0.90f, 0.80f, 0.50f);
	saturn->mass = Constants::Saturn::Mass;
	saturn->radius = Constants::Saturn::Radius;
	saturn->originalMass = saturn->mass;
	saturn->originalRadius = saturn->radius;
	saturn->Name = "Saturn";
	universe.AddBody(saturn);

}

void SolarSystemFactory::CreateUranus(Universe& universe, Mesh& sphereMesh, Texture& uranusTexture) {
	CelestialBody* uranus = new CelestialBody(Constants::Uranus::Mass, Constants::Uranus::Radius);
	uranus->renderable.mesh = &sphereMesh;
	uranus->renderable.material.diffuseTexture = &uranusTexture;
	uranus->transform.position = glm::dvec3(Constants::Uranus::Distance, 0.0f, 0.0f);
	uranus->velocity = glm::dvec3(0.0, Constants::Uranus::OrbitalSpeed, 0.0);
	uranus->trailSettings.color = glm::vec3(0.45f, 0.90f, 1.00f);
	uranus->mass = Constants::Uranus::Mass;
	uranus->radius = Constants::Uranus::Radius;
	uranus->originalMass = uranus->mass;
	uranus->originalRadius = uranus->radius;
	uranus->Name = "Uranus";
	universe.AddBody(uranus);

}

void SolarSystemFactory::CreateNeptune(Universe& universe, Mesh& sphereMesh, Texture& neptuneTexture) {
	CelestialBody* neptune = new CelestialBody(Constants::Neptune::Mass, Constants::Neptune::Radius);
	neptune->renderable.mesh = &sphereMesh;
	neptune->renderable.material.diffuseTexture = &neptuneTexture;
	neptune->transform.position = glm::dvec3(Constants::Neptune::Distance, 0.0f, 0.0f);
	neptune->velocity = glm::dvec3(0.0, Constants::Neptune::OrbitalSpeed, 0.0);
	neptune->trailSettings.color = glm::vec3(0.20f, 0.35f, 1.00f);
	neptune->mass = Constants::Neptune::Mass;
	neptune->radius = Constants::Neptune::Radius;
	neptune->originalMass = neptune->mass;
	neptune->originalRadius = neptune->radius;
	neptune->Name = "Neptune";
	universe.AddBody(neptune);

}



void SolarSystemFactory::CreateSolarSystem(Universe& universe, Mesh& sphereMesh, PlanetTextures& textures) {
	CreateSun(universe, sphereMesh,textures.sun);
	CreateMercury(universe, sphereMesh, textures.mercury);
	CreateVenus(universe, sphereMesh, textures.venus);
	CreateEarth(universe, sphereMesh, textures.earth);
	CreateMars(universe, sphereMesh, textures.mars);
	CreateJupiter(universe, sphereMesh, textures.jupiter);
	CreateSaturn(universe, sphereMesh, textures.saturn);
	CreateUranus(universe, sphereMesh, textures.uranus);
	CreateNeptune(universe,sphereMesh, textures.neptune);
}	