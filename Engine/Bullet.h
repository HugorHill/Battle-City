
#pragma once
#include "MemoryManager.h"


class Bullet : public GameObject {
protected:
	static float BulletSpeed; 
	int direction; //0 - up, 1 - right, 2 - down, 3 - left
	int coordX;
	int coordY;
	float speed_boost;

public:
	void* map;
	static double time;
	Bullet() {};	
	Bullet(int x, int y, int dir,double boost,void* map_);
	void del();
	int getX() { return coordX; }
	int getY() { return coordY; }
	int IsAlive; // состояние 1 летит, 0 - уничтожить
	void init() {};
	void update() ;
	void logic();
	void draw();
	float dist(Bullet a);
	bool operator < (Bullet p) const;
};