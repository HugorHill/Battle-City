#include "Engine.h"
#include "RenderManager.h"
#include <stdio.h>

using namespace std;
Engine* GameObject::engine = NULL;
Engine* Shader::engine = NULL;
Engine* RenderProcessObject::engine = NULL;

Engine::Engine()
{
	GameObject::engine = this;
	Shader::engine = this;
	RenderProcessObject::engine = this;
};

Engine::~Engine()
{

}



void Engine::init()
{
	rm.init(700, 700, this);
}

void Engine::run()
{
	do
	{
		sm.get_current_scene()->calculate();
		rm.updateScreen();
		glfwPollEvents();
	}
	while (!glfwWindowShouldClose(window));
}

GLFWwindow* Engine::getWindow()
{
	return window;
}