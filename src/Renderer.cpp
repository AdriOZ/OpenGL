#include "Renderer.h"

#include <iostream>
#include <string>
#include <unordered_map>

void APIENTRY Renderer::GLLogError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	static std::unordered_map<int32_t, const char*> sourceTypeSeverityToString = {

		/* Sources */
		{GL_DEBUG_SOURCE_API, "API"},
		{GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WINDOW SYSTEM"},
		{GL_DEBUG_SOURCE_SHADER_COMPILER, "SHADER COMPILER"},
		{GL_DEBUG_SOURCE_THIRD_PARTY, "THIRD PARTY"},
		{GL_DEBUG_SOURCE_APPLICATION, "APPLICATION"},
		{GL_DEBUG_SOURCE_OTHER, "OTHER"},
	
		/* Types */
		{GL_DEBUG_TYPE_ERROR, "ERROR"},
		{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED BEHAVIOR"},
		{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "UNDEFINED BEHAVIOR"},
		{GL_DEBUG_TYPE_PORTABILITY, "PORTABILITY"},
		{GL_DEBUG_TYPE_PERFORMANCE, "PERFORMANCE"},
		{GL_DEBUG_TYPE_OTHER, "OTHER"},
		{GL_DEBUG_TYPE_MARKER, "MARKER"},
	
		/* Severities */
		{GL_DEBUG_SEVERITY_HIGH, "HIGH"},
		{GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM"},
		{GL_DEBUG_SEVERITY_LOW, "LOW"},
		{GL_DEBUG_SEVERITY_NOTIFICATION, "NOTIFICATION"}

	};

	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		std::cout << "OpenGL error ["
			<< id << "]: "
			<< sourceTypeSeverityToString[type] << " of "
			<< sourceTypeSeverityToString[severity]
			<< " severity, raised from "
			<< sourceTypeSeverityToString[source] << ": "
			<< msg << "\n";
		__debugbreak();
	}
}

Renderer::Renderer()
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLLogError, nullptr);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh) const
{
	va.Bind();
	ib.Bind();
	sh.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
