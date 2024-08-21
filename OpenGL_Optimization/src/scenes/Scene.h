#pragma once 
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace scene 
{
	class Scene {
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate(float deltaTime){}
		virtual void OnRender(){}
		virtual void OnImGuiRender() {}
	};
}