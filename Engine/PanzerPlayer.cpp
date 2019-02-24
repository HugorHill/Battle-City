#pragma once
#include "PanzerPlayer.h"

PanzerPlayer::PanzerPlayer(int x,int y,int dir,int vel,void*_p,void*_map) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	std_cooldown = 1;
	cooldown = Panzer::std_cooldown;
	engine = _p;
	map = _map;
	texture =  _ptr(engine,Engine)->mm.loadTexture("map/mainhero", true);
}
void PanzerPlayer::logic() {
	if (glfwGetKey(_ptr(engine,Engine)->getWindow(),GLFW_KEY_W) == GLFW_PRESS) {
		direction = 0;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		direction = 1;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		direction = 2;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		direction = 3;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && cooldown <= 0) {
	Panzer::Shoot();
	}
}