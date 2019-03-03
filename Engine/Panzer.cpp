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
	float x0, y0;
	x0 =coordX;
	y0 = coordY;
	switch (direction) {
	case 0:
		y0 += panzer_width;
		break;
	case 1:
		x0 += panzer_width;
		break;
	case 2:
		y0 -= panzer_width;
		break;
	case 3:
		x0 -= panzer_width;
		break;
	}
	Bullet p(x0, y0, direction,engine);
	_ptr(map,Map)->AddBullet(p); // use #include "Defines.h" and write like this: _ptr(map,Map)->AddBullet(p);
	cooldown = std_cooldown;
	immortality_time = std_immortality_time;
}
float  Panzer :: dist(Panzer* a, Panzer* b) {
	float dx = a->getX() - b->getX();
	float dy = a->getY() - b->getY();
	return sqrt(dx*dx + dy * dy);
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

