#include "Engine.h"
#include <stdio.h>
using namespace std;

Engine::~Engine()
{
	for (auto& item : variables)
		delete item.second;
}



void Engine::init()
{
	rm = RenderManager(this);
	rm.init(500, 500);
	current_scene = -1;
}

void Engine::create_var(std::string name, int size)
{
	void* p = (void*)(new char[size]);
	memset(p, 0, size);
	variables.insert(pair<std::string, void*>(name, p));
}

void Engine::push_scene(Scene* scene)
{
	scenes.push_back(scene);
	current_scene = scenes.size() - 1;
}

void Engine::run()
{
	do
	{
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (current_scene!=-1) scenes[current_scene]->calculate();
		rm.updateScreen();
		glfwPollEvents();
	}
	while (!glfwWindowShouldClose(window));
}