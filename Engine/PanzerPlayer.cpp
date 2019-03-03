#pragma once
#include "PanzerPlayer.h"

PanzerPlayer::PanzerPlayer(float x,float y,int dir,float vel,void*_p,void* _map) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	cooldown = 0;
	engine = _p;
	map = _map;
	texture =  _ptr(engine,Engine)->mm.loadTexture("map/mainhero.png");
	time_turn = std_time_turn;
}
void PanzerPlayer::gg() {
	_ptr(engine, Engine)->set_current_scene(0);
}
void PanzerPlayer::logic() {
	velocity = 0;
	if (glfwGetKey(_ptr(engine,Engine)->getWindow(),GLFW_KEY_W) == GLFW_PRESS) {
		direction = 0;
		velocity = std_vel;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		direction = 1;
		velocity = std_vel;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		direction = 2;
		velocity = std_vel;
	}
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		direction = 3;
		velocity = std_vel;
	}
	
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && cooldown <= 0) {
	Shoot();
	}
}