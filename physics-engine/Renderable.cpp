#include"Renderable.h"
#include"Constants.h"
#include"CelestialBody.h"

Renderable::Renderable() {

}

void Renderable::Draw(Shader& shader, Camera& camera,const Transform& transform,double radius,double visualScale) {

	Transform renderTransform = transform;
	renderTransform.position /= Constants::Rendering::DistanceScale;

	double renderRadius = (radius / Constants::Rendering::DistanceScale) * visualScale;

	if (mesh == nullptr) 
		return;
	
	mesh->Draw(shader,
		camera,
		renderTransform.GetMatrix(),
		renderTransform.position,
		renderTransform.rotation,
		renderTransform.scale=glm::vec3(renderRadius),
		material);
}