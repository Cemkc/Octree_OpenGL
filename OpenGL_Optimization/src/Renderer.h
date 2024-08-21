#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
public: 
	void DrawArrays(const VertexArray& va, const Shader& shader) const;
	void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;
};