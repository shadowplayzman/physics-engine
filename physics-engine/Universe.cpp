#include"Universe.h"
#include"CelestialBody.h"
#include"GravitySolver.h"

void Universe::AddBody(CelestialBody* body) {
	bodies.push_back(body);
}

void Universe::Update(float dt) {
	GravitySolver::ApplyGravity(bodies);
	
	
	for (CelestialBody* body : bodies) {
		body->Integrate(dt);
	}
	for (CelestialBody* body : bodies) {
		body->ClearForces();
	}
}