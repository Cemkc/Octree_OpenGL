#include "GameObject.h"
#include <iostream>
#include "scenes/SceneCameraWithCube.h"

glm::vec3 scene::CameraWithCube::cameraPos;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	float lift = glm::length(scene::CameraWithCube::cameraPos - transform.position) * 0.001f;
	transform.position.y += lift;
}
