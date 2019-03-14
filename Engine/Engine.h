#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <soil.h>
#include <map>
#include <string>
#include "Defines.h"
#include "RenderManager.h"
#include "MemoryManager.h"
#include "SceneManager.h"
#include "Gui.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew.lib")



class Engine
{
	friend class RenderManager;
	friend class SceneManager;
	public:
		Engine();
		~Engine();
		void init();
		void run();
		GLFWwindow* getWindow();
		MemoryManager mm;
		RenderManager rm;
		SceneManager sm;
		VariableManager vm;
	private:
		GLFWwindow* window;
};