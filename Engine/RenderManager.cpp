#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
#include <stdio.h>
#include <string>


void RenderManager::init(int w, int h)
{
	std::string title = "";
	if (!glfwInit())
	{
		fprintf(stderr, "Ошибка при инициализации GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_ptr(engine,Engine)->window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	if (_ptr(engine, Engine)->window == NULL)
	{
		fprintf(stderr, "Невозможно открыть окно GLFW\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_ptr(engine, Engine)->window);



	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return;
	}

	glfwSetInputMode(_ptr(engine, Engine)->window, GLFW_STICKY_KEYS, GL_TRUE);
}

void RenderManager::updateScreen()
{
	glfwSwapBuffers(_ptr(engine, Engine)->window);
}

