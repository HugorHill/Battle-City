#pragma once
#include "Panzer.h"
#include "PanzerBot.h"
#include "PanzerPlayer.h"
#include "Bullet.h"
#include "Bonus.h"
#include <vector>
#include <set>

class Map : public GameObject  {
protected:
	std:: vector<PanzerBot> bots;
	std::vector <Bullet> bullets;
	PanzerPlayer player;	
	int CountBot;
	int CountBullet;
	std::vector <float> spawn_botsx;
	std::vector <float> spawn_botsy;
	float spawn_playerx, spawn_playery;
	float spawn_timer; //время с последнего спавна
	
	double time;
	double deltatime;   //время между кадрами
	std::vector<GLuint> textures;
	
public :
	int map[32][32]; // 0- ничего,1- трава, 2- кирпич, 3 - бетон, 4-вода
	void init();
	void draw();
	void logic() ;
	void update();
	void AddBot(PanzerBot p);
	void AddBullet(Bullet p);
	double GetTime();
	void destr(float x0, float y0,int i);

};