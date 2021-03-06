#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
	constexpr uint32_t width = 1024;
	constexpr uint32_t height = width / (16.0f / 9.0f);

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;
		glfwTerminate();
		return 0;
	}

	VertexArray va;
	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f,
	};
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	IndexBuffer ib(indices, 6);
	Shader sh("res/shaders/Basic.shader");

	sh.Bind();
	sh.SetUniform4f("u_Color", 0.4f, 0.5f, 0.6f, 1.0f);
	sh.Unbind();


	Renderer renderer;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		renderer.Draw(va, ib, sh);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

    glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}