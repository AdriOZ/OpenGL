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
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Get the monitor */
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(mode->width, mode->height, "OpenGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;
		glfwTerminate();
		return 0;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexArray va;
	float positions[] = {
		-50.0f, -50.0f,
		 50.0f, -50.0f,
		 50.0f,  50.0f,
		-50.0f,  50.0f,
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

	glm::mat4 proj = glm::ortho(0.0f, (float)mode->width, 0.0f, (float)mode->height, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 translationA = glm::vec3(500.0f, 500.0f, 0.0f);
	glm::vec3 translationB = glm::vec3(300.0f, 300.0f, 0.0f);

	glm::vec3 color = glm::vec3(1.0f, 0.0f, 1.0f);

	Renderer renderer;

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);

	/* Loop until the user closes the window */
	sh.Bind();

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();
		sh.SetUniform4f("u_Color", color.r, color.g, color.b, 1.0f);
		
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			sh.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, sh);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			sh.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, sh);
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::Begin("Test");
			ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, (float)mode->width);
			ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, (float)mode->width);
			ImGui::SliderFloat3("Color", &color.x, 0.0f, 1.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}