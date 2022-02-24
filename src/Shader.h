#pragma once

#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
	void SetUniform1f(const char* name, float v0);
	void SetUniform1i(const char* name, int32_t v0);
private:
	std::string m_FilePath;
	uint32_t m_RendererID;
	std::unordered_map<std::string, int32_t> m_Uniforms;
private:
	static std::tuple<std::string, std::string> ParseShader(const std::string& filepath);
	static uint32_t CompileShader(uint32_t type, const std::string& source);
	int32_t GetUniformLocation(const std::string& name);
};

