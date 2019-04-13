#pragma once
#include "Explosion.h"
#include "Map.h"
void Explosion :: draw() {
	engine->rm.draw_square(_ptr(map, Map)->explosion, expl_size, { coordX,coordY }, 0, lifetime/std_life_time, 16);
	lifetime += _ptr(map, Map)->GetTime();

}
Explosion::Explosion(float x,float y,void*map_) {
	coordX = x;
	coordY = y;
	map = map_;
	lifetime = 0;
	std::cout << "Explosion is creating";
}