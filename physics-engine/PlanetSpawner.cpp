#include"PlanetSpawer.h"
#include"Constants.h"
void PlanetSpawner::loadTemplate() {
	switch (SelectedTemplate) {
	case Template::Earth:
		name = "Earth";
		radiusEarthUnits = 1.0;
		massEarthUnits = 1.0;

		position = glm::dvec3(0.0, Constants::Earth::Distance, 0.0);
		velocity = glm::dvec3(0.0, Constants::Earth::OrbitalSpeed, 0.0);
		trailColor = glm::vec3(0.20f, 0.5f, 1.00f);

		break;
	}
}