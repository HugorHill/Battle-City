#pragma once
#include "Panzer.h"
#include "Bullet.h"
#include "Map.h"

//init some static variables

void* Panzer::map = NULL;
double Panzer::time = 0;


double Panzer::GetCooldown() {
	return cooldown;
}
void Panzer::Shoot() {
	Bullet p(coordX, coordY, direction,engine);
	_ptr(map,Map)->AddBullet(p); // use #include "Defines.h" and write like this: _ptr(map,Map)->AddBullet(p);
	cooldown = std_cooldown;
}


//сделать в апдейте проверку столкновений
void Panzer::update() {

	switch (direction) {
	case 0:
		coordY += velocity * time;
		break;
	case 1:
		coordX += velocity * time;
		break;
	case 2:
		coordY -= velocity * time;
		break;
	case 3:
		coordX -= velocity * time;
		break;
	}

	if (cooldown > -1) {
		cooldown -= Panzer::time;
	}
}
void Panzer::CancelMove() {
	switch(direction) {
	case 0:
		coordY += -velocity * time;
		break;
	case 1:
		coordX += -velocity * time;
		break;
	case 2:
		coordY -= -velocity * time;
		break;
	case 3:
		coordX -= -velocity * time;
		break;
	}

}
void Panzer::draw() {
	glm::vec2 pos = { coordX,coordY };
	float angel=0;
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

