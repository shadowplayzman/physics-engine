#ifndef COLLIDER_H
#define COLLIDER_H

#include<glm/glm.hpp>

enum class ColliderType
{
	Sphere,
	Box,
	Capsule,
	Plane

};


class Collider {
	public:
		ColliderType type;

		Collider(ColliderType type);
		virtual ~Collider() = default;
};

class SphereCollider :public Collider {
	public:
		float radius;

		SphereCollider(float radius);
};

class BoxCollider :public Collider {
	public:
		glm::vec3 halfExtents;

		BoxCollider(const glm::vec3& halfExtents);
};

class CapsuleCollider :public Collider {
	public:
		float radius;
		float height;

		CapsuleCollider(float radius, float height);
};

class PlaneCollider :public Collider {
	public:
		glm::vec3 normal;
		float distance;

		PlaneCollider(const glm::vec3& normal, float distance);
};
#endif // !COLLIDER_H

