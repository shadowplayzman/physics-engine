#include"Renderable.h"
#include"Constants.h"

Renderable::Renderable() {

}

void Renderable::Draw(Shader& shader, Camera& camera,const Transform& transform) {

	Transform renderTransform = transform;
	renderTransform.position /= Constants::Rendering::RenderScale;
	if (mesh == nullptr) 
		return;
	
	mesh->Draw(shader,
		camera,
		renderTransform.GetMatrix(),
		renderTransform.position,
		renderTransform.rotation,
		renderTransform.scale,
		material);
	std::cout << renderTransform.position.x << " "
		<< renderTransform.position.y << '\n';
}