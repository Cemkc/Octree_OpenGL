#pragma once

#include "Transform.h"
#include <VertexArray.h>
#include <Shader.h>

class GameObject {
public:
	Transform transform;
	glm::vec4 color;
	VertexArray* VAO = nullptr;
	Shader* Shader = nullptr;

	GameObject();
	~GameObject();

	void Update();
};