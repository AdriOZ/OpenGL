#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

Shader::Shader(const std::string& filePath) : m_FilePath(filePath)
{
	auto [vertexSource, fragmentSource] = ParseShader(filePath);
	m_RendererID = glCreateProgram();
	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
	glAttachShader(m_RendererID, vs);
	glAttachShader(m_RendererID, fs);
	glLinkProgram(m_RendererID);
	glValidateProgram(m_RendererID);
	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

std::tuple<std::string, std::string> Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		None = -1,
		Vertex = 0,
		Fragment = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::None;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::Fragment;
			}
		}
		else
		{
			ss[static_cast<int32_t>(type)] << line << std::endl;
		}
	}
	return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int32_t result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int32_t lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = new char[lenght];
		glGetShaderInfoLog(id, lenght, &lenght, message);
		std::cout << message << std::endl;
		glDeleteShader(id);
		delete[]message;
		return 0;
	}

	return id;
}

int32_t Shader::GetUniformLocation(const std::string& name)
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		return m_Uniforms[name];
	}
	int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
	m_Uniforms[name] = location;
	return location;
}
