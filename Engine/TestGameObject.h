#pragma once
#include "Engine.h"
#include "MemoryManager.h"

class TestGameObject : public GameObject
{
	public:
		TestGameObject() {};
		~TestGameObject() {};
		void init();
		void draw();
		void update() {};
		void logic() {};
	private:
		GLuint texture;
		struct{
			GLuint VAO;
			GLuint pos;
			GLuint tex;
			Shader shader;
		}square;
};