#include "SceneCameraWithCube.h"

scene::CameraWithCube::CameraWithCube()
	:
	m_ImGuiIO(ImGui::GetIO()),
	texture1(Texture("res/textures/square_gimp.png"))
{

	m_Window = glfwGetCurrentContext();
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
		CameraWithCube* scene = static_cast<CameraWithCube*>(glfwGetWindowUserPointer(window));
		scene->OnCursorPos(xpos, ypos);

		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent((float)xpos, (float)ypos);
	});	

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

	SetMouseMode(MouseMode::CAMERA);

	CameraWithCube::cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	m_VAO = new VertexArray();
	m_VertexBuffer =  new VertexBuffer(vertices, 36, 5 * 36 * sizeof(float));
	m_Bufferlayout = new VertexBufferLayout();
	m_Bufferlayout->Push<float>(3);
	m_Bufferlayout->Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, *m_Bufferlayout);

	m_Shader = new Shader();

	m_Shader->AttachShader(GL_VERTEX_SHADER, "res/shaders/color_shader/vertexShader.glsl");
	m_Shader->AttachShader(GL_FRAGMENT_SHADER, "res/shaders/color_shader/fragmentShader.glsl");
	m_Shader->CreateLinkProgram();

	float margin = 3.0f;
	float xpos = 0;
	float ypos = 0;

	unsigned int numberOfObjects = 16;

	for (int i = 0; i < numberOfObjects; i++) {
		m_GameObjects.push_back(new GameObject);
		m_GameObjects[i]->VAO = m_VAO;
		m_GameObjects[i]->Shader = m_Shader;
		m_GameObjects[i]->transform.scale = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	}

	unsigned int rows = static_cast<unsigned int>(std::floor(std::sqrt(numberOfObjects)));
	unsigned int cols = rows;
	unsigned int remainder = numberOfObjects - (rows * cols);

	if (remainder > 0) rows += 1;

	unsigned int objectIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (objectIndex >= numberOfObjects) break;

			float x = i * margin;
			float z = j * margin;

			glm::vec3 position(x, 0.0f, z);

			m_GameObjects[objectIndex]->transform.position = position;

			objectIndex++;
		}
	}

	m_Shader->Bind(); // don't forget to activate/use the shader before setting uniforms!

	m_Shader->setUniform1i("texture1", 0);

	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	m_Shader->setUniformMat4("projection", projection);

	float weight = 0;
	m_Shader->setUniform1f("weight", weight);
	
}

scene::CameraWithCube::~CameraWithCube()
{
	delete m_VAO;
	delete m_VertexBuffer;
	delete m_Bufferlayout;
	delete m_Shader;
}

void scene::CameraWithCube::OnUpdate(float deltaTime)
{

	for (GameObject* gameObject : m_GameObjects) {
		gameObject->Update();
	}
}

void scene::CameraWithCube::OnRender()
{
	debugKeyPrevious = debugKeyPressed;
	escapeKeyPrevious = escapeKeyPressed;

	// Call custom input processing logic
	processInput(m_Window);

	if (debugKeyPrevious != debugKeyPressed) {
		if (debugKeyPressed) debugKeySwitchHigh = true;
		else debugKeySwitchLow = true;
	}

	if (escapeKeyPrevious != escapeKeyPressed) {
		if (escapeKeyPressed) escapeKeySwitchHigh = true;
		else escapeKeySwitchLow = true;
	}

	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Clear window
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture1.Bind(0);

	//if (upKey) {
	//	weight = weight + 0.002f;
	//	if (weight < 0.0f) weight = 0.0f;
	//	else if (weight > 1.0f) weight = 1.0f;
	//	m_Shader->setUniform1f("weight", weight);
	//}
	//if (downKey) {
	//	weight = weight - 0.002f;
	//	if (weight < 0.0f) weight = 0.0f;
	//	else if (weight > 1.0f) weight = 1.0f;
	//	m_Shader->setUniform1f("weight", weight);
	//}

	glm::vec3 cameraTarget;
	cameraTarget = CameraWithCube::cameraPos + cameraFront;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::cross(worldUp, cameraFront);
	glm::vec3 cameraUp = glm::cross(cameraFront, cameraRight);
	view = glm::lookAt(CameraWithCube::cameraPos, cameraTarget, cameraUp);

	if (escapeKeySwitchHigh) {
		if (m_MouseMode == MouseMode::CAMERA) SetMouseMode(MouseMode::CURSOR);
		else if (m_MouseMode == MouseMode::CURSOR) SetMouseMode(MouseMode::CAMERA);
	}

	m_Shader->setUniformMat4("view", view);

	for (GameObject* gameObject : m_GameObjects) {
		m_Renderer.DrawGameObject(*gameObject);
	}

	debugKeySwitchHigh = false;
	debugKeySwitchLow = false;

	escapeKeySwitchHigh = false;
	escapeKeySwitchLow = false;

}

void scene::CameraWithCube::OnImGuiRender()
{
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}
}

void scene::CameraWithCube::processInput(GLFWwindow* window)
{

	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		CameraWithCube::cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		CameraWithCube::cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		CameraWithCube::cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		CameraWithCube::cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		escapeKeyPressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
	{
		escapeKeyPressed = false;
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

void scene::CameraWithCube::OnCursorPos(double xpos, double ypos)
{
	if (firstMouse) // initially set to true
	{
		mouseLastX = xpos;
		mouseLastY = ypos;
		firstMouse = false;
	}

	if (m_MouseMode == MouseMode::CURSOR) {
		firstMouse = true;
		return;
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

void scene::CameraWithCube::SetMouseMode(MouseMode mode) {

	m_MouseMode = mode;

	switch (m_MouseMode)
	{
	case CAMERA:
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		break;
	case CURSOR:
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		break;
	default:
		break;
	}
}
