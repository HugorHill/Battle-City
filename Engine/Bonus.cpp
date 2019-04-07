#pragma once 
#include "Bonus.h"
double Bonus::time = 0;

Bonus::Bonus(double x, double y, int t) {
	coordX = x;
	coordY = y;
	type = t;
	lifetime = std_bonus_lifetime;
	texture = engine->mm.loadTexture("map/base.jpg");
	time = 0;	
}
void Bonus::del(PanzerPlayer* player) {
	player->upgrade(type);
	lifetime = 0;
}

void Bonus::update() {
	lifetime -= time;
	
}

void Bonus::draw() {
	if (lifetime > 0) {
		glm::vec2 pos = { coordX,coordY };
		engine->rm.draw_square(texture, 2 * bonus_width, pos, 0);
	}
}

 