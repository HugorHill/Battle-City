#include <iostream>
#include "Engine.h"
#include "Gui.h"
#include "Map.h"
#include "DynamicMap.h"

void init_scenes(Engine* engine)
{

	Scene* mainMenu = new Scene(engine);
	mainMenu->push_gameObject(new gui::Menu);
	mainMenu->init();
	engine->push_scene(mainMenu);

	

	Scene* onePlayer = new Scene(engine);
	onePlayer->push_gameObject(new Map);
	onePlayer->init();
	engine->push_scene(onePlayer);

	Scene* twoPlayers = new Scene(engine);
	twoPlayers->push_gameObject(new gui::PassWindow);
	twoPlayers->init();
	engine->push_scene(twoPlayers);



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