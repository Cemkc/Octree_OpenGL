#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexBufferAttribute 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) 
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		return 0;
	}
};

class VertexBufferLayout 
{
private:
	std::vector<VertexBufferAttribute> m_Attrib;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Attrib.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferAttribute::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Attrib.push_back( { GL_UNSIGNED_INT, count, GL_FALSE } );
		m_Stride += count * VertexBufferAttribute::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Attrib.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferAttribute::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferAttribute> GetAttributes() const { return m_Attrib; }
	inline unsigned int GetStride() const { return m_Stride; }
};