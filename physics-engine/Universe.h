#ifndef UNIVERSE_H
#define UNIVERSE_H

#include<vector>

class CelestialBody;

class Universe {
	public:
		std::vector<CelestialBody*> bodies;
		CelestialBody* GetBody(size_t index);
		size_t BodyCount() const;

		void AddBody(CelestialBody* body);

		void Update(double dt);
};

#endif // !UNIVERSE_H

