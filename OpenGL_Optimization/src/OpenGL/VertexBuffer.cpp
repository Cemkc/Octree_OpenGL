#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int count, unsigned int size)
	: m_VertexCount(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

unsigned int VertexBuffer::GetVertexCount() const
{
	return m_VertexCount;
}
