
#pragma once
#include "MemoryManager.h"


class Scene
{
	public:
		Scene() : engine(NULL) {};
		Scene(void* _engine):engine(_engine) {};
		~Scene();
		void push_gameObject(GameObject* obj); // добавление объекта к сцене
		void calculate(); // просчет сцены
		void init(); // init all gameObject
	private:
		void* engine; //указатель на движок, который рисует сцену
		std::vector<GameObject*> gameObjects; // список всех используемых объектов на сцене
};