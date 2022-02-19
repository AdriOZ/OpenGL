#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void APIENTRY GLLogError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);