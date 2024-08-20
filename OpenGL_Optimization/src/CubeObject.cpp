//#pragma once
//
//#include <GL/glew.h>
//#include <GLM/vec3.hpp>
//#include <array>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//class Cube {
//private:
//	std::array<float, 180> *vertices;
//
//	Cube(glm::vec3 position) {
//		*vertices = {
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//
//
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//
//			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//
//			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//
//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//
//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//		};
//
//	}
//
//	void AllocateVetrices() {
//		unsigned int VAO, VBO;
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(1, &VBO);
//
//		glBindVertexArray(VAO);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		// position attribute
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		// texture coord attribute
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(1);
//
//		// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//		glBindVertexArray(0);
//	}
//
//	void SetTexture(const char* texturePath) {
//		unsigned int texture1, texture2;
//		// texture 1
//		// ---------
//		glGenTextures(1, &texture1);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		// set the texture wrapping parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		// set texture filtering parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//		// load image, create texture and generate mipmaps
//		int width, height, nrChannels;
//		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//		unsigned char* data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			glGenerateMipmap(GL_TEXTURE_2D);
//		}
//		else
//		{
//			std::cout << "Failed to load texture" << std::endl;
//		}
//		stbi_image_free(data);
//	}
//
//};
