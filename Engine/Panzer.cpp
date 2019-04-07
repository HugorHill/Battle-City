#pragma once
#include "Panzer.h"
#include "Bullet.h"
#include "Map.h"

//init some static variables

void* Panzer::map = NULL;
double Panzer::time = 0;
int Panzer::getDir() {
	return direction;
}
float Panzer::getVel() {
	return velocity;
}
/*Panzer::~Panzer() {
	engine->mm.delTexture(texture);
}*/
double Panzer::GetCooldown() {
	return cooldown;
}
void Panzer::Shoot() {
	float x0, y0;
	x0 =coordX;
	y0 = coordY;
	switch (direction) {
	case 0:
		y0 += 1.4*panzer_width;
		break;
	case 1:
		x0 += 1.4*panzer_width;
		break;
	case 2:
		y0 -= 1.4*panzer_width;
		break;
	case 3:
		x0 -= 1.4*panzer_width;
		break;
	}
	Bullet p(x0, y0, direction,speed_boost);
	_ptr(map,Map)->AddBullet(p); // use #include "Defines.h" and write like this: _ptr(map,Map)->AddBullet(p);
	cooldown = std_cooldown/speed_boost;
	//immortality_time =(immortality_time < std_immortality_time) ? std_immortality_time:immortality_time;
}
float  Panzer :: dist(Panzer* a, Panzer* b) {
	float dx = a->getX() - b->getX();
	float dy = a->getY() - b->getY();
	return sqrt(dx*dx + dy * dy);
}

//сделать в апдейте проверку столкновений
void Panzer::update() {
	if (stun_time > -1) {
		stun_time -= time;
	}
	if (stun_time < 0) {
		switch (direction) {
		case 0:
			coordY += velocity * time;
			break;
		case 1:
			coordX +=  velocity * time;
			break;
		case 2:
			coordY -=  velocity * time;
			break;
		case 3:
			coordX -=  velocity * time;
			break;
		}
	}

	if (cooldown > -1) {
		cooldown -= Panzer::time;
	}
}
void Panzer::CancelMove() {
	switch(direction) {
	case 0:
		coordY +=  velocity * time;
		break;
	case 1:
		coordX +=  velocity * time;
		break;
	case 2:
		coordY -=  velocity * time;
		break;
	case 3:
		coordX -=  velocity * time;
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
	engine->rm.draw_square(texture, 2*panzer_width, pos, angel);
}
void Panzer::del() {
	health--;
	if (health <= 0) {
		IsAlive = 0;
		engine->mm.delTexture(texture);
	}
}
