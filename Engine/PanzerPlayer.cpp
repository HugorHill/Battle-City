#pragma once
#include "PanzerPlayer.h"
#include <string>
#include "Map.h"

//std::string mainhero[5] = { "map/mainhero0.png","map/mainhero1.png","map/mainhero2.png",
//"map/mainhero3.png","map/mainhero4.png" };

PanzerPlayer::PanzerPlayer(float x,float y,int dir,float vel,void* _map) {
	coordX = x;
	coordY = y;
	velocity = vel;
	direction = dir;
	IsAlive = 1;
	cooldown = 0;
	map = _map;
	level = 1;
	//texture =  engine->mm.loadTexture("Panzer/T1-0.png");
	time_turn = std_time_turn;	
	speed_boost = (level-1)/6.0+1;
	health = 3;
	stun_time = 0;
	immortality_time = std_immortality_time;
	swap_time = 0;
}
void PanzerPlayer::gg() {
	_ptr(map,Map)->EndGame();
	engine->sm.set_cur_scene("main menu");
}
void PanzerPlayer::logic() {
	engine->vm.setVar("hero position", &glm::vec2(coordX, coordY));
	velocity = 0;
	if (glfwGetKey(engine->getWindow(),GLFW_KEY_W) == GLFW_PRESS) {
		direction = 0;
		velocity = std_vel;
	}
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		direction = 1;
		velocity = std_vel;
	}
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		direction = 2;
		velocity = std_vel;
	}
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		direction = 3;
		velocity = std_vel;
	}
	
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && cooldown <= 0) {
	Shoot();
	}
}
void PanzerPlayer::upgrade(int type) {
	switch (type) {
	case 1: if (level < 4) {
		level++;
		speed_boost = sqrt((double)level);
	}
			break;
	case 2: health++;
		break;
	case 3:
		_ptr(map,Map)->destroy_them_all();
		break;
	case 4:
		_ptr(map,Map)->stun_them_all() ;
		break;
	/*case 5:
		map->save_base();
		break;*/
	case 6:
		immortality_time = std_immortality_time_bonus;
		break;
	}
}

void PanzerPlayer::del() {
	Panzer::del();
	if (level > 1) {
		level--;
		speed_boost = sqrt((double)level);
	}
}
void PanzerPlayer::draw() {
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
	engine->rm.draw_square(_ptr(map, Map)->player_textures[level-1], 2 * panzer_width, pos,
		angel, swap_time, 8);
}

