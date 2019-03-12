
#pragma once
#include "MemoryManager.h"


class Scene
{
	public:
		Scene(){};
		~Scene();
		void push_gameObject(GameObject* obj); // добавление объекта к сцене
		void calculate(); // просчет сцены
		void init(); // init all gameObject
	private:
		std::vector<GameObject*> gameObjects; // список всех используемых объектов на сцене
};