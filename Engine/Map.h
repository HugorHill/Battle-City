#pragma once
#include "Panzer.h"
#include "PanzerBot.h"
#include "PanzerPlayer.h"
#include "Bullet.h"
#include "Bonus.h"
#include "Explosion.h"
#include <vector>
#include <set>

class Map : public GameObject  {
protected:
	std:: vector <PanzerBot> bots;
	std::vector <Bullet> bullets;
	std::vector<Bonus>bonuses;
	std::vector<Explosion> exp;
	PanzerPlayer player;	
	int CountBot;
	int CountBullet;
	long long int frags;
	std::vector <float> spawn_botsx;
	std::vector <float> spawn_botsy;
	float spawn_playerx, spawn_playery;
	float spawn_timer; //время с последнего спавна
	
	double time;
	double deltatime;   //время между кадрами
	std::vector<GLuint> textures;
	
	
public :
	std::vector <GLuint> player_textures;
	GLuint bot_texture;
	GLuint bullet_texture;
	GLuint explosion;
	int map[32][32]; // 0- ничего,1- трава, 2- кирпич, 3 - бетон, 4-вода
	void init();
	void draw();
	void logic() ;
	void update();
	void AddBot(PanzerBot p);
	void AddBullet(Bullet p);
	void destroy_them_all();
	void stun_them_all();
	double GetTime();
	void destr(float x0, float y0, Bullet* b);
	void AddBonus(int type);
	void EndGame();
};