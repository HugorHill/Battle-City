#pragma once 
#include "Bonus.h"

Bonus::Bonus(int x, int y, int t) {
	coordX = x;
	coordY = y;
	type = t;
	lifetime = std_bonus_lifetime;
	texture =  _ptr(engine,Engine)->mm.loadTexture("map/base.png");
	
}
void Bonus::del(PanzerPlayer* player) {
	player->upgrade(type);
	lifetime = 0;
}

void Bonus::update() {
	lifetime -= time;
}

void Bonus::draw() {
	glm::vec2 pos = { coordX,coordY };
	engine->rm.drawSquare(texture, 2 * bonus_width, pos, 0);
}

 