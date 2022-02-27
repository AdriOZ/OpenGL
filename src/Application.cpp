#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Get the monitor */
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	std::cout << mode->width << " x " << mode->height;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(mode->width, mode->height, "OpenGL", NULL, NULL);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float positions[] = {
		-50.0f, -50.0f, 0.0f,   0.0f,
		 50.0f, -50.0f, 100.0f, 0.0f,
		 50.0f,  50.0f, 100.0f, 100.0f,
		-50.0f,  50.0f, 0.0f,   100.0f
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);
	glm::mat4 proj = glm::ortho(0.0f, (float)mode->width, 0.0f, (float)mode->height, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(500.0f, 500.0f, 0.0f));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(500.0f, 500.0f, 0.0f));
	glm::mat4 mvp = proj * view * model;

	
	Shader sh("res/shaders/Basic.shader");
	sh.Bind();
	sh.SetUniform1i("u_Texture", 0);
	sh.SetUniformMat4f("u_MVP", mvp);
	sh.Unbind();

	Renderer renderer;

	Texture te("res/textures/avatar.png");
	te.Bind();


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

	glfwTerminate();
	return 0;
}