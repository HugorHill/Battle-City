#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
#include <stdio.h>
#include <string>
#include "RP_DrawSquare.h"
#include "RP_DrawText.h"
#include "RP_DrawShadows.h"

void Layer::init()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glGenTextures(1, &texturebuffer);
	glBindTexture(GL_TEXTURE_2D, texturebuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_SIZE_PIXELS, WIN_SIZE_PIXELS, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texturebuffer, 0);
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_SIZE_PIXELS, WIN_SIZE_PIXELS);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

void Layer::Use()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
};

void Layer::Reset()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

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


	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderProcess.insert(std::pair<std::string, RenderProcessObject*>("draw square", new RP_DrawSquare));
	renderProcess["draw square"]->init();
	renderProcess.insert(std::pair<std::string, RenderProcessObject*>("draw text", new RP_DrawText));
	renderProcess["draw text"]->init();
	renderProcess.insert(std::pair<std::string, RenderProcessObject*>("draw shadow", new RP_DrawShadows));
	renderProcess["draw shadow"]->init();


	layers.insert(std::pair<std::string, Layer*>("screen", new Layer));
	layers["screen"]->framebuffer = 0;
	layers.insert(std::pair<std::string, Layer*>("main", new Layer));
	layers["main"]->init();
	layers["main"]->Use();
}

void RenderManager::updateScreen()
{
	draw_square(layers["main"]->texturebuffer, WINDOW_SIZE_UNITS, glm::vec2(0));
	renderProcess["draw square"]->render(layers["screen"]);
	glfwSwapBuffers(engine->window);
	for (auto layer : layers)
	{
		layer.second->Use();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		layer.second->Reset();
	}
}

//функция рисования квадратика: размеры и позиция указываются в юнитах, а угол в градусах
void RenderManager::draw_square(GLuint texture, GLuint size, glm::vec2 pos, float angelRotate,float time,int countFrame)
{
	RP_DrawSquare* RP = (RP_DrawSquare*)renderProcess["draw square"];
	RP->options.push_back({texture, size, pos, angelRotate,time,countFrame });
}

void RenderManager::render_squares()
{
	RP_DrawSquare* RP = (RP_DrawSquare*)renderProcess["draw square"];
	RP->render(layers["main"]);
}

//поизиция указывается в юнитах
void RenderManager::draw_text(std::string text, glm::vec2 pos, bool atCenter, glm::vec3 color, float scale, GLuint bgTexture)
{
	RP_DrawText* RP = (RP_DrawText*)renderProcess["draw text"];
	RP->options = { text, pos, atCenter, color, scale, bgTexture };
	RP->render(layers["main"]);
}

//запихиваем очередную преграду в массив
void RenderManager::draw_shadow(glm::vec2 light_position,glm::vec2 wall)
{
	RP_DrawShadows* RP = (RP_DrawShadows*)renderProcess["draw shadow"];
	RP->options.push_back({light_position,wall});
}

void RenderManager::render_shadows()
{
	RP_DrawShadows* RP = (RP_DrawShadows*)renderProcess["draw shadow"];
	RP->render(layers["main"]);
}