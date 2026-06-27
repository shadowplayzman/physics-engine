#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include<glm/glm.hpp>
struct Transform;
class Collider;

class Rigidbody {
	public:
		Transform* transform=nullptr;
		Collider* collider = nullptr;
		

		float mass;
		float inverseMass;

		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 accumulatedForce=glm::vec3(0.0f);

		bool useGravity = true;

		Rigidbody(float mass = 1.0f);

		void AddForce(const glm::vec3& force);

		void Integrate(float dt);

		void ClearForces();
};



#endif
