#include"SkySphere.h"
#include"PrimitiveMeshFactory.h"

SkySphere::SkySphere() :mesh(PrimitiveMeshFactory::CreateSphere(1.0f,64,64)),
						texture("stars.jpg","diffuse",0),
						shader("skysphere.vert","skysphere.frag")
{
	material.diffuseTexture = &texture;


	material.diffusecolor = glm::vec3(1.0f);
	material.specularColor = glm::vec3(0.0f);

	material.shininess = 0.0f;
	material.emissive = 1.0f;
	material.emissionStrength = 1.0f;



}
void SkySphere::Draw(Camera& camera)
{
    shader.Activate();

    glDepthMask(GL_FALSE);

    glCullFace(GL_FRONT);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), camera.Position);
    model = glm::scale(model, glm::vec3(50000.0f));

    mesh.Draw(
        shader,
        camera,
        model,
        camera.Position,
        glm::quat(glm::vec3(0.0f)),
        glm::vec3(50000.0f),
        material
    );

    glCullFace(GL_BACK);
    glDepthMask(GL_TRUE);
}