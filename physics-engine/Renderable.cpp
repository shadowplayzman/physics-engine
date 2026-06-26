#include"Renderable.h"

Renderable::Renderable() {

}

void Renderable::Draw(Shader& shader, Camera& camera) {
	if (mesh == nullptr) {
		return;
	}
	mesh->Draw(shader,
		camera,
		transform.GetMatrix(),
		transform.position, 
		transform.rotation,
		transform.scale,
		material);
}