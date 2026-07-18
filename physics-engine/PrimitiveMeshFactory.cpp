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
Mesh PrimitiveMeshFactory::CreateRing(float innerRadius, float outerRadius, int segments) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	const float PI = 3.14159;

	for (int i = 0;i <= segments;i++) {
		float angle = 2.0f * PI * i / segments;

		float c = cos(angle);
		float s = sin(angle);

		Vertex inner;
		inner.position = glm::vec3(innerRadius * c, 0.0f, innerRadius * s);

		inner.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		inner.color = glm::vec3(1.0f);
		inner.texUV = glm::vec2(0.0f, (float)i / segments);

		Vertex outer;
		outer.position = glm::vec3(outerRadius * c, 0.0f, outerRadius * s);

		outer.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		outer.color = glm::vec3(1.0f);
		outer.texUV = glm::vec2(1.0f, (float)i / segments);

		vertices.push_back(inner);
		vertices.push_back(outer);

	}
	const int frontVertexCount = vertices.size();

	for (int i = 0; i < frontVertexCount; i++)
	{
		Vertex back = vertices[i];

		back.normal *= -1.0f;

		vertices.push_back(back);
	}
	for (int i = 0;i < segments;i++) {
		int inner1 = i * 2;
		int outer1 = inner1 + 1;

		int inner2 = (i + 1) * 2;
		int outer2 = inner2 + 1;

		indices.push_back(inner1);
		indices.push_back(outer1);
		indices.push_back(inner2);

		indices.push_back(outer1);
		indices.push_back(outer2);
		indices.push_back(inner2);
	}
	int offset = frontVertexCount;

	for (int i = 0; i < segments; i++)
	{
		int inner1 = offset + i * 2;
		int outer1 = inner1 + 1;

		int inner2 = offset + (i + 1) * 2;
		int outer2 = inner2 + 1;

		// Reverse winding order
		indices.push_back(inner1);
		indices.push_back(inner2);
		indices.push_back(outer1);

		indices.push_back(outer1);
		indices.push_back(inner2);
		indices.push_back(outer2);
	}

	return Mesh(vertices, indices);
}