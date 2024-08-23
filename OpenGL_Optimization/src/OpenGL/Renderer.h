#pragma once

#include "ExceptionHandling.h"

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GameObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Renderer {
private:
	VertexArray* m_VAO;
	Shader* m_Shader;

	glm::mat4 m_Model = glm::mat4(1.0f);

public: 
	Renderer();
	~Renderer();

	void DrawGameObject(const GameObject& go);
	void DrawArrays(const VertexArray& va, const Shader& shader) const;
	void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;
};