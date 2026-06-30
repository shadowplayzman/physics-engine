
#ifndef GRAVITY_SOLVER_H
#define GRAVITY_SOLVER_H

#include<vector>

class CelestialBody;

class GravitySolver {
	public:
		static void ApplyGravity(std::vector<CelestialBody*>& bodies);
};

#endif // !GRAVITY_SOLVER_H

