#pragma once

class VertexBuffer 
{
private:
	unsigned int m_RendererID;
	unsigned int m_VertexCount;
public:
	VertexBuffer(const void* data, unsigned int count, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetVertexCount() const;
};