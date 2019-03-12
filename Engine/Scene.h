
#pragma once
#include "MemoryManager.h"


class Scene
{
	public:
		Scene(){};
		~Scene();
		void push_gameObject(GameObject* obj); // ���������� ������� � �����
		void calculate(); // ������� �����
		void init(); // init all gameObject
	private:
		std::vector<GameObject*> gameObjects; // ������ ���� ������������ �������� �� �����
};