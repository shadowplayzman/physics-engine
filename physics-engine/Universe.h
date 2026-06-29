#ifndef UNIVERSE_H
#define UNIVERSE_H

#include<vector>

class CelestialBody;

class Universe {
	public:
		std::vector<CelestialBody*> bodies;
		void AddBody(CelestialBody* body);

		void Update(float dt);
};

#endif // !UNIVERSE_H

