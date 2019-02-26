#pragma once
#include "PanzerBot.h"
PanzerBot::PanzerBot(float x, float y, int dir, float vel, void*_p, void* _map,int type) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	cooldown = 0;
	engine = _p;
	map = _map;
	switch (type) {
	case 1:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer1.jpg");
	case 2:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer2.jpg");
	case 3:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer3.jpg");
	}
}
void PanzerBot::logic() {


}