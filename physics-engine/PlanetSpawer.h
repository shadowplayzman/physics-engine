#ifndef PLANET_SPAWNER_H
#define PLANET_SPAWNER_H

#include<string>
#include<glm/glm.hpp>

class Universe;
class Mesh;

struct PlanetSpawner
{
	enum class Template {
		Custom,
		Mercury,
		Venus,
		Earth,
		Mars,
		Jupiter,
		Saturn,
		Uranus,
		Neptune,
		Sun
	};
	Template SelectedTemplate = Template::Custom;

	std::string name = "New Planet";

	double mass = 5.972e24;
	double radius = 6.371e6;

	glm::dvec3 position = glm::dvec3(0.0);
	glm::dvec3 velocity = glm::dvec3(0.0);

	glm::vec3 trailColor = glm::vec3(1.0f);
	glm::vec3 planetColor = glm::vec3(1.0f);

	bool preserveDensity = true;

	void loadTemplate();
	void Spawn(Universe& universe, Mesh& sphereMesh);
};

#endif // !PLANET_SPAWNER_H

