#include "Scene.h"
#include "Engine.h"

Scene::~Scene()
{
	for (auto &item : gameObjects) delete item;
}

void Scene::push_gameObject(GameObject * obj)
{
	gameObjects.push_back(obj);
}

void Scene::calculate()
{
	int count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
		gameObjects[i]->draw();
		gameObjects[i]->logic();
		gameObjects[i]->update();
	}
}