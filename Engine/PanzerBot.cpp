#pragma once
#include "PanzerBot.h"
PanzerBot::PanzerBot(float x, float y, int dir, float vel, void* _map,int type) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	cooldown = 0;
	speed_boost = 1;
	map = _map;
	time_turn = std_time_turn;
	immortality_time = std_immortality_time;
	stun_time = -1;
	switch (type) {
	case 1:
		texture = engine->mm.loadTexture("map/panzer1.png");
		break;
	case 2:
		texture = engine->mm.loadTexture("map/panzer2.png");
		break;
	case 3:
		texture = engine->mm.loadTexture("map/panzer3.png");
		break;
	}
}
bool PanzerBot::operator <(PanzerBot p) const {
	return (coordX < p.coordX);
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