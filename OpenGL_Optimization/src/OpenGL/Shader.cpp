#pragma once

#include "Shader.h"

Shader::Shader() 
	: m_RendererID(0)
{
	
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::AssignShader(unsigned int type, const std::string& filePath)
{
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::AttachShader(unsigned int shaderType, const char* filepath)
{
	if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER) {
		std::cout << "Invalid shader type!";
		return;
	}
	std::string shaderCode = ReadShaderFile(shaderType, filepath);
	unsigned int shader = CompileShader(shaderType, shaderCode);

	m_Shaders.push_back(shader);
}

void Shader::CreateLinkProgram()
{
	// shader program
	m_RendererID = glCreateProgram();
	for (unsigned int shader : m_Shaders) {
		glAttachShader(m_RendererID, shader);
	}
	glLinkProgram(m_RendererID);
	// print linking errors if any
	int success;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
			infoLog << std::endl;
	}

	for (unsigned int shader : m_Shaders) {
		glDeleteShader(shader);
	}
}

std::string Shader::ReadShaderFile(unsigned int shaderType, const char* shaderFilePath)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// open files
		shaderFile.open(shaderFilePath);
		std::stringstream shaderStream, fShaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode;
}

unsigned int Shader::CompileShader(unsigned int shaderType, const std::string& sourceCode)
{
	if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER) {
		std::cout << "Given shader type couldn't been found." << std::endl;
		return 0;
	}
	unsigned int shaderID = glCreateShader(shaderType);
	const char* src = sourceCode.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		int lenght;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(shaderID, lenght, &lenght, message);
		std::cout << "ERROR::SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" <<
			message << std::endl;
		glDeleteShader(shaderID);
		return 0;
	}

	return shaderID;
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 vec)
{
	glUniform4f(GetUniformLocation(name), vec.r, vec.g, vec.b, vec.a);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) 
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		std::cout << "WARNING: Uniform " << name << " does not exist" << std::endl;
	}

	m_UniformLocationCache[name] = location;
	
	return location;
}
