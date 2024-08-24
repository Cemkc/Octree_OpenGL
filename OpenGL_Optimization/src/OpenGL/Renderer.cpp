#include "Renderer.h"

Renderer::Renderer()
	:m_VAO(nullptr), m_Shader(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::DrawGameObject(const GameObject& go)
{
	if (m_VAO != go.VAO) {
		go.VAO->Bind();
		m_VAO = go.VAO;
	}
	if (m_Shader != go.Shader) {
		go.Shader->Bind();
		m_Shader = go.Shader;
	}

	m_Model = glm::translate(m_Model, go.transform.position);
	m_Model = glm::scale(m_Model, go.transform.scale);
	m_Shader->setUniformMat4("model", m_Model);
	m_Shader->SetUniform4f("color", go.color);

	GLCall(glDrawArrays(GL_TRIANGLES, 0, go.VAO->GetVertexCount()));

	m_Model = glm::mat4(1.0f);
}

void Renderer::DrawArrays(const VertexArray& va, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, va.GetVertexCount());
}

void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}


void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}