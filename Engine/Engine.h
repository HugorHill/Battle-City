
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
#include "Gui.h"

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
		void init(); // ������������� ���� ���������� ��� ���������� ������
		void create_var(std::string name, int size); // �������� ����� ���������� ���������� ��� ������
		void push_scene(Scene* scene); // �������� ����� � ������
		void run(); // ���������������� ������ ������������ ����� ������
		void set_current_scene(int currScene) { current_scene = currScene; }
		GLFWwindow* getWindow(); //u can get the pointer of current window
		MemoryManager mm;
		RenderManager rm;
	private:
		GLFWwindow* window;
		std::map<std::string, void*> variables;
		std::vector<Scene*> scenes;
		int current_scene;
};