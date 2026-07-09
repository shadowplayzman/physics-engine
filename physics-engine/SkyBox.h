#ifndef SKYBOX_H
#define SKYBOX_H

#include"Camera.h"
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"

#include<GL/glew.h>
#include<vector>
#include<string>


class Skybox
{
public:
	Skybox(const std::vector<std::string>& faces);

	void Draw(Camera& camera);

private:
	GLuint VAO = 0;
	GLuint VBO = 0;

	GLuint cubemapTexture = 0;

	Shader shader;

	GLuint LoadCubemap(const std::vector<std::string>& faces);
	void SetupMesh();
};
#endif // !SKYBOX_H

