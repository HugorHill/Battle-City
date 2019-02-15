
#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <soil.h>
#include <map>
#include <string>
#include "Defines.h"
#include "RenderManager.h"
#include "MemoryManager.h"
#include "Scene.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew.lib")



class Engine
{
	friend class Scene;
	friend class RenderManager;
	public:
		Engine() {};
		~Engine();
		void init(); // инициализация всех прееменных для корректной работы
		void create_var(std::string name, int size); // создание новой глобальной переменной для движка
		void push_scene(Scene* scene); // добавние сцены в список
		void run(); // непосредственный запуск бесконечного цикла движка
		MemoryManager mm;
		RenderManager rm;
	private:
		GLFWwindow* window;
		std::map<std::string, void*> variables;
		std::vector<Scene*> scenes;
		int current_scene;
};