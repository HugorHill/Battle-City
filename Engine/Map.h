#pragma once
#include "Panzer.h"
#include "PanzerBot.h"
#include "PanzerPlayer.h"
#include "Bullet.h"
#include <vector>

class Map : public GameObject  {
protected:
	PanzerBot bots[100];
	PanzerPlayer player;
	Bullet bullets[200];
	int map[35][35]; // 0- ������,1- �����, 2- ������, 3 - �����, 4-����
public :
	void init(void* p);
	void draw();
	void logic() ;
	void update();


};