#pragma once
#include "Panzer.h"
#include "PanzerBot.h"
#include "PanzerPlayer.h"
#include "Bullet.h"
#include <vector>
#include <set>

class Map : public GameObject  {
protected:
	std:: vector<PanzerBot> bots;
	std::vector <Bullet> bullets;
	PanzerPlayer player;	
	int CountBot;
	int CountBullet;
	
	double time;
	double deltatime;   //����� ����� �������
	std::vector<GLuint> textures;
	
public :
	int map[32][32]; // 0- ������,1- �����, 2- ������, 3 - �����, 4-����
	void init(void* p);
	void draw();
	void logic() ;
	void update();
	void AddBot(PanzerBot p);
	void AddBullet(Bullet p);
	double GetTime();

};