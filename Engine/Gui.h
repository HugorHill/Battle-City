#pragma once
#include "Engine.h"
#include "Defines.h"
#include "MemoryManager.h"
#include <iostream>
#include <string>

namespace gui
{

	class Menu : public GameObject
	{
		public:
			Menu() {};
			~Menu() {};
			void init(void* p);
			void draw();
			void logic();
			void update() {};
		private:
			GLuint bgTextTexture;
			GLuint pointerTexture;
			int current_button;
			GLFWwindow* window;
			RenderManager* rm;
	};

	class PassWindow : public GameObject
	{
		public:
			PassWindow() {};
			~PassWindow() {};
			void init(void* p);
			void draw();
			void logic();
			void update() {};
		private:
			GLFWwindow* window;
			RenderManager* rm;
			float timer;
	};
}
