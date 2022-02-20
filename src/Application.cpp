#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "OpenGL", NULL, NULL);
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

	/* Debug messages */
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLLogError, nullptr);

	VertexArray va;

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	IndexBuffer ib(indices, 6);
	ib.Bind();

	Shader sh("res/shaders/Basic.shader");
	sh.Bind();

	std::string uniform = "u_Color";
	float r = 0.2f;
	float g = 0.3f;
	float b = 0.8f;
	float increment = 0.005f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		sh.SetUniform4f(uniform, r, g, b, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if (r > 1.0f)
		{
			increment = -0.005f;
		}
		else if (r < 0.0f)
		{
			increment = 0.005f;
		}
		r += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}