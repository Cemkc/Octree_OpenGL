#include "GameObject.h"
#include <iostream>
#include "scenes/SceneCameraWithCube.h"

glm::vec3 scene::CameraWithCube::cameraPos;

GameObject::GameObject()
	: color(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f))
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (glm::length(scene::CameraWithCube::cameraPos - transform.position) < 1.5f) {
		color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}

	double sum = 0.0;
	for (int i = 0; i < 10000; ++i) {
		sum += sqrt(i * 0.001);
	}

}
