#pragma once
// #include <stdio.h>
#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "scenes/Scene.h"
#include "scenes/SceneCameraWithCube.h"
#include "scenes/SceneMenu.h"

#include "CommonData.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Window Dimensions
const unsigned int WIDTH = 800, HEIGHT = 600;

using namespace scene;

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

	glfwSwapInterval(0);

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

	sceneMenu->RegisterScene<CameraWithCube>("Demo Scene");

	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	int frameCount = 0;
	float fps = 0.0f;

	

	while (!glfwWindowShouldClose(mainWindow))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentScene) {
			currentScene->OnUpdate(0.0f);
			currentScene->OnRender();

			ImGui::Begin("Scene");

			if (currentScene == sceneMenu) {

				ImGui::Text("Number of objects to spawn: ");

				ImGui::InputScalar("Unsigned Integer", ImGuiDataType_U32, &CommonData::CubeNumber);

				ImGui::Text("Algorithm To Use: ");

				std::string algoButtonText = CommonData::AlgorithmMethodToString();
				if (ImGui::Button(algoButtonText.c_str())) {
					if (CommonData::AlgoMethod == CommonData::AlgorithmMethod::BRUTE_FORCE) {
						CommonData::AlgoMethod = CommonData::AlgorithmMethod::OCTREE;
						algoButtonText = "OCTREE";
					}
					else if (CommonData::AlgoMethod == CommonData::AlgorithmMethod::OCTREE) {
						CommonData::AlgoMethod = CommonData::AlgorithmMethod::BRUTE_FORCE;
						algoButtonText = "BRUTE_FORCE";
					}
					else {
						algoButtonText = "##";
					}
				}

				ImGui::Text("Object Initialization Method: ");

				std::string spawnMethodButtonText = CommonData::InitMethodToString();
				if (ImGui::Button(spawnMethodButtonText.c_str())) {
					if (CommonData::InitMethod == CommonData::InitializationMethod::RANDOM) {
						CommonData::InitMethod = CommonData::InitializationMethod::GRID;
						spawnMethodButtonText = "GRID";
					}
					else if (CommonData::InitMethod == CommonData::InitializationMethod::GRID) {
						CommonData::InitMethod = CommonData::InitializationMethod::RANDOM;
						spawnMethodButtonText = "RANDOM";
					}
					else {
						spawnMethodButtonText = "##";
					}
				}

				ImGui::Spacing();
			}

			ImGui::Text("Start Scene: ");

			if (currentScene != sceneMenu && ImGui::Button("<-")) {
				delete currentScene;
				currentScene = sceneMenu;
			}

			CommonData::FrameRate = fps;

			currentScene->OnImGuiRender();

			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Increment frame count
		frameCount++;

		// Calculate time since last update
		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> elapsedTime = currentTime - startTime;

		if (elapsedTime.count() >= 1.0f) { // Every second
			fps = frameCount / elapsedTime.count();
			frameCount = 0;
			startTime = currentTime;
		}

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

	

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}