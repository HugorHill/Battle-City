
#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <map>
#include <string>
#include <glm\glm.hpp>
#include "Shader.h"

#define WINDOW_SIZE_UNITS 512

class RenderManager
{

	public:
		RenderManager() : engine(NULL) {};
		RenderManager(void* ptr) : engine(ptr) {};
		~RenderManager() {};
		void init(int w, int h);
		void updateScreen();

		void drawSquare(GLuint texture,GLuint size,glm::vec2 pos,float angelRotate = 0);
		
	private:
		void* engine; // указатель на движок
		struct
		{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}square;
};