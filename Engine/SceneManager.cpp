#include "SceneManager.h"

void SceneManager::push_scene(Scene* scene, std::string name)
{
	list_scenes.insert(std::pair<std::string, Scene*>(name, scene));
}

void SceneManager::destroy_scene(std::string name)
{
	list_scenes[name]->~Scene();
	list_scenes.erase(name);
}

Scene * SceneManager::get_current_scene()
{
	return list_scenes[current_scene];
}

void SceneManager::set_cur_scene(std::string name)
{
	current_scene = name;
}

//эту штуку надо будет переделать
void SceneManager::reset_scene(std::string name)
{
	list_scenes[name]->~Scene();
	list_scenes[name]->init();
}