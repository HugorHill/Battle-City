
#pragma once
#include "MemoryManager.h"
#include "Shader.h"

class Terrain : public GameObject
{
	public:
		Terrain() {};
		void init(void* p);
		void draw();
		void logic() {};
		void update() {};
	private:
		GLuint texture;
};
//функция поворота текстуры танка (координаты, угол в градусах)
//функция рисования объекта

