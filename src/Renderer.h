#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer
{
public:
	Renderer();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh) const;
	void Clear() const;
private:
	static void APIENTRY GLLogError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);
};