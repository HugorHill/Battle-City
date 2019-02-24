#include "Engine.h"
#include "Gui.h"
#include <iostream>




void init_scenes(Engine* engine)
{
	Scene* mainMenu = new Scene(engine);
	mainMenu->push_gameObject(new gui::Menu);
	mainMenu->init();
	engine->push_scene(mainMenu);

	

	Scene* onePlayers = new Scene(engine);
	onePlayers->push_gameObject(new gui::PassWindow);
	onePlayers->init();
	engine->push_scene(onePlayers);


	engine->push_scene(onePlayers);



	engine->set_current_scene(0);
}

int main()
{
	Engine game;
	game.init();
	init_scenes(&game);
	game.run();
	return 0;
}