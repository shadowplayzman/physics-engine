#include"PrimitiveMeshFactory.h"
Mesh PrimitiveMeshFactory::CreateSphere(float radius, int sectors, int stacks) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	const float PI = 3.14159265359f;

	for (int i = 0;i <= stacks;i++) {
		float stackAngle = PI / 2.0f - i * PI / stacks;

		float xy = radius * cos(stackAngle);
		float z = radius * sin(stackAngle);

		for (int j = 0; j <= sectors; j++)
		{
			float sectorAngle = j * 2.0f * PI / sectors;
			float x = xy * cos(sectorAngle);
			float y = xy * sin(sectorAngle);

			Vertex vertex;
			vertex.position = glm::vec3(x, z, y);
			vertex.normal = glm::normalize(vertex.position);
			vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);
			vertex.texUV = glm::vec2((float)j / sectors, (float)i / stacks);

			vertices.push_back(vertex);


		}
	}
	for (int i = 0;i < stacks;i++) {
		int K1 = i * (sectors + 1);
		int K2 = K1 + sectors + 1;

		for (int j = 0;j < sectors;j++) {
			if (i != 0) {
				indices.push_back(K1);
				indices.push_back(K2);
				indices.push_back(K1 + 1);
			}
			if (i != (stacks - 1)) {
				indices.push_back(K1 + 1);
				indices.push_back(K2);
				indices.push_back(K2 + 1);

			}
			K1++;
			K2++;
		}
	}
	return Mesh(vertices, indices);
}