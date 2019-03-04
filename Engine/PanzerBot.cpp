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
	time_turn = std_time_turn;
	switch (type) {
	case 1:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer1.png");
		break;
	case 2:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer2.png");
		break;
	case 3:
		texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer3.png");
		break;
	}
}
void PanzerBot::logic() {
	int r = rand()%100;
	if (r < 10 && time_turn <= 0) {
		direction = r % 4;
		time_turn = std_time_turn;
	}
	if (cooldown <= 0 && r < 5) {
		Shoot();
	} 
}