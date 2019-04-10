#pragma once
#include "PanzerBot.h"
std::string name_b[8] = {
	"Panzer/T0-0.png","Panzer/T0-1.png","Panzer/T0-2.png","Panzer/T0-3.png",
	"Panzer/T0-4.png","Panzer/T0-5.png","Panzer/T0-6.png","Panzer/T0-7.png"
};

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
	health = 1;
	texture.reserve(8);
	texture.resize(8);
	switch (type) {
	case 1:
		for (int i = 0; i < 8; i++) {
			texture[i] = engine->mm.loadTexture(name_b[i]);
		}
		break;
	case 2:
		for (int i = 0; i < 8; i++) {
			texture[i] = engine->mm.loadTexture(name_b[i]);
		}
		break;
	case 3:
		for (int i = 0; i < 8; i++) {
			texture[i] = engine->mm.loadTexture(name_b[i]);
		}
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
	++num_texture % 8;
}