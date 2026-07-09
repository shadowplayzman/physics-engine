#include"Renderable.h"
#include"Constants.h"
#include"CelestialBody.h"
#include<cmath>

Renderable::Renderable() {

}

void Renderable::Draw(Shader& shader, Camera& camera,const Transform& transform,double radius) {

	Transform renderTransform = transform;
	renderTransform.position /= Constants::Rendering::DistanceScale;

	double renderRadius = CalculateRenderRadius(radius);

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
 double Renderable::CalculateRenderRadius(double radius) {
	constexpr double RadiusExponent = 0.4;
	constexpr double ScaleFactor = 0.0035;

	return ScaleFactor * std::pow(radius, RadiusExponent);
}