#include "Engine.h"
#include "Terrain.h"
#include <iostream>






Scene* create_Scene(void* p)
{
	Scene* scene = new Scene(p);
	scene->push_gameObject(new Terrain(p));
	return scene;
};

int main()
{
	Engine game;
	game.init();
	game.push_scene(create_Scene(&game));
	game.run();
	return 0;
}