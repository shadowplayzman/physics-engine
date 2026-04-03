#include"Universe.h"
#include"CelestialBody.h"
#include"GravitySolver.h"

//to add bodies into the universe class
void Universe::AddBody(CelestialBody* body) {
	bodies.push_back(body);
}

//updates the universe and calls function like apply gravity,forces etc
void Universe::Update(double dt) {
	GravitySolver::ApplyGravity(bodies);
	
	
	for (CelestialBody* body : bodies) {
		body->Integrate(dt);
	}
	for (CelestialBody* body : bodies) {
		body->ClearForces();
	}
}

CelestialBody* Universe::GetBody(size_t index) {
	return bodies[index];
}
size_t Universe::BodyCount()const {
	return bodies.size();
}