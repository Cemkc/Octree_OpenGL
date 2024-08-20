#pragma once

#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	m_vertexCount = vb.GetVertexCount();
	const auto& attributes = layout.GetAttributes();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attributes.size(); i++) 
	{
		const auto& attribute = attributes[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized, layout.GetStride(), (const void*) offset);
		offset += attribute.count * VertexBufferAttribute::GetSizeOfType(attribute.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

unsigned int VertexArray::GetVertexCount() const
{
	return m_vertexCount;
}
