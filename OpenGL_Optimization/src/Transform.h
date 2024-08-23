#pragma once

#include "GLM/glm.hpp"

class Transform {
public:
	glm::vec3 position;
	glm::vec3 scale;

	Transform();
	~Transform();
};