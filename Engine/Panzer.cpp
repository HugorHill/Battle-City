#pragma once
#include "Panzer.h"
#include "Bullet.h"
#include "Map.h"

//init some static variables
double Panzer::std_cooldown = 1;

void* Panzer::map = NULL;
double Panzer::time = 0;


double Panzer::GetCooldown() {
	return cooldown;
}
void Panzer::Shoot() {
	Bullet p(coordX, coordY, direction);
	_ptr(map,Map)->AddBullet(p); // use #include "Defines.h" and write like this: _ptr(map,Map)->AddBullet(p);
	cooldown = Panzer::std_cooldown;
}



void Panzer::update() {
	if (direction == 0) {
		coordY += velocity * time;
	}
	if (direction == 1) {
		coordX += velocity * time;
	}
	if (direction == 2) {
		coordY -= velocity * time;
	}
	if (direction == 3) {
		coordX -= velocity * time;
	}
}
void Panzer::draw() {
	glm::vec2 pos = { coordX,coordY };
	float angel;
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
	_ptr(engine, Engine)->rm.drawSquare(texture, 24, pos, angel);
}
