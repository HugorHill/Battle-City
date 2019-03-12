#pragma once
#include <map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager() {};
	~SceneManager() {};
	Scene* get_current_scene();
	void push_scene(Scene* scene,std::string name);
	void destroy_scene(std::string name);

	void set_cur_scene(std::string name);
	void reset_scene(std::string name);
private:
	std::map<std::string, Scene*> list_scenes;
	std::string current_scene;
};

