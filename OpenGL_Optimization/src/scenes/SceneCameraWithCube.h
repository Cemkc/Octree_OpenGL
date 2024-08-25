#pragma once

#include "Scene.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GameObject.h"
#include "Octree.h"

#include "GLMUtils.h"

enum MouseMode {
	CAMERA,
	CURSOR
};

namespace scene {
	class CameraWithCube : public Scene {
	private:
		Renderer m_Renderer;
		VertexArray* m_VAO;
		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_Bufferlayout;
		Shader* m_Shader;

		Texture texture1;

		// std::vector<Camera*> m_cameras;
		std::vector<GameObject*> m_GameObjects;
		Octree<GameObject>* m_Octree;
		BoundingBox* m_Bounds;

		bool show_demo_window = true;
		bool show_another_window = false;
		// ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGuiIO& m_ImGuiIO;

		GLFWwindow* m_Window;
		bool upKey = false;
		bool downKey = false;
		bool debugKeyPressed = false;
		bool debugKeyPrevious = false;
		bool debugKeySwitchHigh = false;
		bool debugKeySwitchLow = false;

		bool escapeKeyPressed = false;
		bool escapeKeyPrevious = false;
		bool escapeKeySwitchHigh = false;
		bool escapeKeySwitchLow = false;

		// camera
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		float yaw = glm::radians(90.0f); // Horizontal angle, start at 90 degrees
		float pitch = glm::radians(90.0f);   // Vertical angle, start at 90 degrees
		const float radius = 1.0f;        // Distance from the target point
		float sensitivity = 0.02f;         // Movement sensitivity

		// Timing 
		float deltaTime = 0.0f; // Time before current frame and last frame
		float lastFrame = 0.0f;

		MouseMode m_MouseMode = MouseMode::CAMERA;
		float mouseLastX = 400, mouseLastY = 300;
		bool firstMouse = true;

		float weight = 0.0f;
		glm::mat4 m_IdentityMat = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);

		void processInput(GLFWwindow* window);
		void OnCursorPos(double xpos, double ypos);
		void SetMouseMode(MouseMode mode);

	public:
		static glm::vec3 cameraPos;

		CameraWithCube();
		~CameraWithCube();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void InitWindow(GLFWwindow* window) { m_Window = window; }

		void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
			if (firstMouse) // initially set to true
			{
				mouseLastX = (float)xpos;
				mouseLastY = (float)ypos;
				firstMouse = false;
			}

			float xoffset = xpos - mouseLastX;
			float yoffset = mouseLastY - ypos; // reversed: y ranges bottom to top
			mouseLastX = xpos;
			mouseLastY = ypos;
			const float sensitivity = 0.1f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

		}
	};
}
