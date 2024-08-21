#include "SceneClearColor.h"

#include <GL/glew.h>
#include "imgui/imgui.h"

namespace scene
{
	SceneClearColor::SceneClearColor()
		:m_ClearColor { 0.2f, 0.3f, 0.3f, 1.0f }
	{
	}
	SceneClearColor::~SceneClearColor()
	{
	}
	void SceneClearColor::OnUpdate(float deltaTime)
	{
	}
	void SceneClearColor::OnRender()
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void SceneClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}