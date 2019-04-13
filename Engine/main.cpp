#include <iostream>
#include "Engine.h"
#include "Gui.h"
#include "Map.h"
#include "TestGameObject.h"

void init_scenes(Engine* engine)
{

	Scene* mainMenu = new Scene();
	mainMenu->push_gameObject(new gui::Menu);
	mainMenu->init();
	engine->sm.push_scene(mainMenu,"main menu");

	

	Scene* onePlayer = new Scene();
	onePlayer->push_gameObject(new Map);
	onePlayer->init();
	engine->sm.push_scene(onePlayer,"one player");

	Scene* twoPlayers = new Scene();
	twoPlayers->push_gameObject(new TestGameObject);
	twoPlayers->init();
	engine->sm.push_scene(twoPlayers,"pass window");



	engine->sm.set_cur_scene("main menu");
}

int main()
{
	Engine game;
	game.init();
	init_scenes(&game);
	game.run();
	return 0;
}