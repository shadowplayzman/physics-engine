#include"Collider.h"

Collider::Collider(ColliderType type) {
	this->type = type;
}

SphereCollider::SphereCollider(float radius)
	: Collider(ColliderType::Sphere) 
{
	this->radius = radius;
}

BoxCollider::BoxCollider(const glm::vec3& halfExtents)
	: Collider(ColliderType::Box)
{
	this->halfExtents = halfExtents;
}

CapsuleCollider::CapsuleCollider(float radius,float height)
	: Collider(ColliderType::Capsule)
{
	this->radius = radius;
	this->height = height;
}

PlaneCollider::PlaneCollider(const glm::vec3& normal,float distance)
	: Collider(ColliderType::Plane)
{
	this->normal = normal;
	this->distance = distance;
}