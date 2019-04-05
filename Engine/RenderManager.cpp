#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
#include <stdio.h>
#include <string>
#include "RP_DrawSquare.h"
#include "RP_DrawText.h"

void RenderManager::init(int w, int h, Engine* ptr)
{
	engine = ptr;
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

	engine->window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	if (engine->window == NULL)
	{
		fprintf(stderr, "Невозможно открыть окно GLFW\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(engine->window);
	//glfwSwapInterval(0);


	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return;
	}

	//glfwSetInputMode(engine->window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	renderProcess.insert(std::pair<std::string, RenderProcessObject*>("draw square", new RP_DrawSquare));
	renderProcess["draw square"]->init();
	renderProcess.insert(std::pair<std::string, RenderProcessObject*>("draw text", new RP_DrawText));
	renderProcess["draw text"]->init();

}

void RenderManager::updateScreen()
{
	glfwSwapBuffers(engine->window);
}

//функция рисования квадратика: размеры и позиция указываются в юнитах, а угол в градусах
void RenderManager::drawSquare(GLuint texture, GLuint size, glm::vec2 pos, float angelRotate)
{
	RP_DrawSquare* RP = (RP_DrawSquare*)renderProcess["draw square"];
	RP->options = {texture, size, pos, angelRotate };
	RP->run();
}

//поизиция указывается в юнитах
void RenderManager::drawText(std::string text, glm::vec2 pos, bool atCenter, glm::vec3 color, float scale, GLuint bgTexture)
{
	RP_DrawText* RP = (RP_DrawText*)renderProcess["draw text"];
	RP->options = { text, pos, atCenter, color, scale, bgTexture };
	RP->run();
}