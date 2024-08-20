#include "Renderer.h"

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
