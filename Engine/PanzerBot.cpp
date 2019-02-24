#pragma once
#include "PanzerBot.h"
PanzerBot::PanzerBot(int x, int y, int dir, int vel, void*_p, void*_map, int type) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	std_cooldown = 1;
	cooldown = Panzer::std_cooldown;
	engine = _p;
	map = _map;
	switch (type) {
	case 1:
			texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer1", true);
	case 2:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer2", true);
	case 3:
	texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer3", true);
	}
}
void PanzerBot::logic() {


}