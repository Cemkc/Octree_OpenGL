#include "SceneMenu.h"
#include <imgui/imgui.h>
#include <GL/glew.h>
#include <iostream>

namespace scene {
	SceneMenu::SceneMenu(Scene*& currenScenePtr)
		: m_CurrentScene(currenScenePtr)
	{
	}

	SceneMenu::~SceneMenu()
	{
	}

	void SceneMenu::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void SceneMenu::OnImGuiRender()
	{
		for (auto& scene : m_Scenes) {
			if (ImGui::Button(scene.first.c_str())) {
				m_CurrentScene = scene.second();
			}
		}
	}
}