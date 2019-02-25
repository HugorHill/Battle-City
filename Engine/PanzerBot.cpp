#pragma once
#include "PanzerBot.h"
PanzerBot::PanzerBot(float x, float y, int dir, float vel, void*_p, void* _map,int type) {
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
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer1.jpg", true);
	case 2:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer2.jpg", true);
	case 3:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer3.jpg", true);
	}
}
void PanzerBot::logic() {


}