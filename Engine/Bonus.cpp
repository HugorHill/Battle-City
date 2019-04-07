#pragma once 
#include "Bonus.h"
double Bonus::time = 0;
std::string text[7] = { "map/bonus0.jpg","map/bonus1.jpg","map/bonus2.jpg",
"map/bonus3.jpg","map/bonus4.jpg", "map/bonus5.jpg","map/bonus6.jpg" };

Bonus::Bonus(double x, double y, int t) {
	coordX = x;
	coordY = y;
	type = t;
	lifetime = std_bonus_lifetime;
	texture = engine->mm.loadTexture(text[t]);
	time = 0;	
}
void Bonus::del(PanzerPlayer* player) {
	player->upgrade(type);
	lifetime = 0;
	flag = true;
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

 