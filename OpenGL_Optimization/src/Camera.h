#pragma once

#include "GameObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera : public GameObject {
public:
	Camera();
	~Camera();
	
	glm::mat4 GetView() {

	}
};