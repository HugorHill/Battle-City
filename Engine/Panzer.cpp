#pragma once
#include "Panzer.h"

Panzer :: Panzer(int x, int y, int vel, int dir) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	std_cooldown = 1;
	cooldown = Panzer::std_cooldown;
}
double Panzer::GetCooldown() {
	return cooldown;
}

void Panzer::init(void*p) {
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

}
