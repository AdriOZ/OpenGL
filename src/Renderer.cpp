#include "Renderer.h"

#include <iostream>
#include <string>
#include <unordered_map>

void APIENTRY GLLogError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	static std::unordered_map<int32_t, const char*> sources = {
		{GL_DEBUG_SOURCE_API, "API"},
		{GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WINDOW SYSTEM"},
		{GL_DEBUG_SOURCE_SHADER_COMPILER, "SHADER COMPILER"},
		{GL_DEBUG_SOURCE_THIRD_PARTY, "THIRD PARTY"},
		{GL_DEBUG_SOURCE_APPLICATION, "APPLICATION"},
		{GL_DEBUG_SOURCE_OTHER, "OTHER"}
	};

	static std::unordered_map<int32_t, const char*> types = {
		{GL_DEBUG_TYPE_ERROR, "ERROR"},
		{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED BEHAVIOR"},
		{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "UNDEFINED BEHAVIOR"},
		{GL_DEBUG_TYPE_PORTABILITY, "PORTABILITY"},
		{GL_DEBUG_TYPE_PERFORMANCE, "PERFORMANCE"},
		{GL_DEBUG_TYPE_OTHER, "OTHER"},
		{GL_DEBUG_TYPE_MARKER, "MARKER"}
	};

	static std::unordered_map<int32_t, const char*> severities = {
		{GL_DEBUG_SEVERITY_HIGH, "HIGH"},
		{GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM"},
		{GL_DEBUG_SEVERITY_LOW, "LOW"},
		{GL_DEBUG_SEVERITY_NOTIFICATION, "NOTIFICATION"}
	};


	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		std::cout << "OpenGL error ["
			<< id << "]: "
			<< types[type] << " of "
			<< severities[severity]
			<< " severity, raised from "
			<< sources[source] << ": "
			<< msg << "\n";
		__debugbreak();
	}
}