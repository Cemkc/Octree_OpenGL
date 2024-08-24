#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include <string>
#include <vector>
#include <unordered_map>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
private:
	unsigned int m_RendererID;
	std::vector<unsigned int> m_Shaders;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader();
	~Shader();

	void AssignShader(unsigned int type, const std::string& filePath);

	void Bind() const;
	void Unbind() const;

	void AttachShader(unsigned int shaderType, const char* filepath);

	void CreateLinkProgram();

	std::string ReadShaderFile(unsigned int shaderType, const char* shaderFilePath);

	unsigned int CompileShader(unsigned int shaderType, const std::string& sourceCode);

	void setUniform1i(const std::string& name, int value);

	void setUniform1f(const std::string& name, float value);

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniform4f(const std::string& name, glm::vec4 vec);

	void setUniformMat4(const std::string& name, const glm::mat4& mat);

	int GetUniformLocation(const std::string& name);

};