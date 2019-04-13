#pragma once
#include "PanzerBot.h"
#include "Map.h"
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
	swap_time = 0;
	/*switch (type) {
	case 1:
		texture = engine->mm.loadTexture("Panzer/P0-0.png");
		break;
	case 2:
		texture = engine->mm.loadTexture("Panzer/P0-0.png");
		break;
	case 3:
		texture = engine->mm.loadTexture("Panzer/P0-0.png");
		break;
	}*/
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
void PanzerBot::draw() {

	glm::vec2 pos = { coordX,coordY };
	float angel = 0;
	switch (direction) {
	case 0: angel = 90;
		break;
	case 1: angel = 0;
		break;
	case 2:
		angel = 270;
		break;
	case 3:
		angel = 180;
		break;
	}
	engine->rm.draw_square(_ptr(map, Map)->bot_texture, 2 * panzer_width, pos,
		angel, swap_time, 8);
}