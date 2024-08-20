#pragma once
// #include <stdio.h>
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
std::string printMatrix(const glm::mat4& matrix);
std::string printVector3(const glm::vec3& vec);

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

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(mainWindow, mouse_callback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed!";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,


		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,


		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,


		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,


		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,


		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2, // Behind square first triangle
		1, 2, 3, // Behind square second triangle
		4, 5, 6, // Front square first triangle
		5, 6, 7, // Front square second triangle
		0, 4, 1,
		1, 4, 5,
		2, 6, 3,
		3, 6, 7
	};

	{
		VertexArray va;
		VertexBuffer vb(vertices, 36, 5 * 36 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		// IndexBuffer ib(indices, 6);

		Shader shader;
		shader.AttachShader(GL_VERTEX_SHADER, "res/shaders/vertexShader.glsl");
		shader.AttachShader(GL_FRAGMENT_SHADER, "res/shaders/fragmentShader.glsl");
		shader.CreateLinkProgram();

		Texture texture1("res/textures/container.jpg");
		Texture texture2("res/textures/awesomeface.png");

		Renderer renderer;
		shader.Bind(); // don't forget to activate/use the shader before setting uniforms!

		shader.setUniform1i("texture1", 0);
		shader.setUniform1i("texture2", 1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		shader.setUniformMat4("projection", projection);

		float weight = 0;
		shader.setUniform1f("weight", weight);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		// Loop until window closed
		while (!glfwWindowShouldClose(mainWindow))
		{
			debugKeyPrevious = debugKeyPressed;

			// Call custom input processing logic
			processInput(mainWindow);

			if (debugKeyPrevious != debugKeyPressed) {
				if (debugKeyPressed) debugKeySwitchHigh = true;
				else debugKeySwitchLow = true;
			}

			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Clear window
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			texture1.Bind(0);
			texture2.Bind(1);

			if (upKey) {
				weight = weight + 0.002f;
				if (weight < 0.0f) weight = 0.0f;
				else if (weight > 1.0f) weight = 1.0f;
				shader.setUniform1f("weight", weight);
			}
			if (downKey) {
				weight = weight - 0.002f;
				if (weight < 0.0f) weight = 0.0f;
				else if (weight > 1.0f) weight = 1.0f;
				shader.setUniform1f("weight", weight);
			}

			glm::vec3 cameraTarget;
			cameraTarget = cameraPos + cameraFront;
			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(direction);

			glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 cameraRight = glm::cross(worldUp, cameraFront);
			glm::vec3 cameraUp = glm::cross(cameraFront, cameraRight);
			view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

			if (debugKeySwitchHigh) {
				std::cout << "Camera Position: \n" << printVector3(cameraPos);
				std::cout << "Camera Right: \n" << printVector3(cameraRight);
				std::cout << "Camera Up: \n" << printVector3(cameraUp);
				std::cout << "View: \n" << printMatrix(view);
			}

			shader.setUniformMat4("model", model);
			shader.setUniformMat4("view", view);

			renderer.DrawArrays(va, shader);
			// glDrawArrays(GL_TRIANGLES, 0, 36);

			debugKeySwitchHigh = false;
			debugKeySwitchLow = false;

			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Get + Hanlde user input events
			glfwPollEvents();
			glfwSwapBuffers(mainWindow);
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		//glDeleteVertexArrays(1, &VAO);
		//glDeleteBuffers(1, &VBO);
		//glDeleteBuffers(1, &EBO);

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		
		glfwTerminate();

	}

	return 0;
}

void processInput(GLFWwindow* window)
{

	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		upKey = true;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
		upKey = false;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		downKey = true;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
		downKey = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		debugKeyPressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		debugKeyPressed = false;
	}

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) // initially set to true
	{
		mouseLastX = xpos;
		mouseLastY = ypos;
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

std::string printVector3(const glm::vec3& vec) {
	std::ostringstream result;
	result << vec.x << " " << vec.y << " " << vec.z << " " << std::endl;
	return result.str();
}

std::string printMatrix(const glm::mat4& matrix) {
	std::ostringstream result;
	for (unsigned int j = 0; j < 4; j++) {
		for (unsigned int i = 0; i < 4; i++) {
			result << " | " << matrix[i][j] << " | ";
		}
		result << std::endl;
	}
	return result.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}