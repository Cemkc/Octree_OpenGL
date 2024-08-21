#pragma once
// #include <stdio.h>
#include <iostream>
#include <unordered_map>

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

#include "scenes/Scene.h"
#include "scenes/SceneClearColor.h"
#include "scenes/SceneCameraWithCube.h"
#include "scenes/SceneMenu.h"

using namespace scene;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Window Dimensions
const unsigned int WIDTH = 800, HEIGHT = 600;

// input booleans
bool upKey;
bool downKey;
bool debugKeyPressed = false;
bool debugKeyPrevious = false;
bool debugKeySwitchHigh = false;
bool debugKeySwitchLow = false;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = glm::radians(90.0f); // Horizontal angle, start at 90 degrees
float pitch = glm::radians(90.0f);   // Vertical angle, start at 90 degrees
const float radius = 1.0f;        // Distance from the target point
float sensitivity = 0.02f;         // Movement sensitivity

// Timing 
float deltaTime = 0.0f; // Time before current frame and last frame
float lastFrame = 0.0f;

float mouseLastX = 400, mouseLastY = 300;
bool firstMouse = true;

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed!";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No backwards compatibality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibality
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cout << "GLFW window creation failed!";
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set contect gor GLEW to use
	glfwMakeContextCurrent(mainWindow);
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed!";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		Scene* currentScene = nullptr;
		SceneMenu* sceneMenu = new SceneMenu(currentScene);
		currentScene = sceneMenu;

		sceneMenu->RegisterScene<SceneClearColor>("Clear Color");
		sceneMenu->RegisterScene<CameraWithCube>("Camera With Cube");

		while (!glfwWindowShouldClose(mainWindow))
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentScene) {
				currentScene->OnUpdate(0.0f);
				currentScene->OnRender();

				ImGui::Begin("Scene");

				if (currentScene != sceneMenu && ImGui::Button("<-")) {
					delete currentScene;
					currentScene = sceneMenu;
				}
				currentScene->OnImGuiRender();

				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Get + Hanlde user input events
			glfwPollEvents();
			glfwSwapBuffers(mainWindow);
		}

		if (currentScene != sceneMenu) {
			delete currentScene;
		}
		delete sceneMenu;

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		
		glfwTerminate();

	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}