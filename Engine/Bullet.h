
#pragma once
#include "MemoryManager.h"


class Bullet : public GameObject {
protected:
	int IsAlive; // состояние 1 летит, 0 - уничтожить
	static int BulletSpeed; 
	int direction; //0 - up, 1 - right, 2 - down, 3 - left
	int coordX;
	int coordY;
	GLuint texture;
public:
	
	static double time;
	Bullet(int x, int y, int dir);
	void del();
	int getX() { return coordX; }
	int getY() { return coordY; }
	Bullet(void* p) {};
	void init(void *p) ;
	void update() ;
	void logic();
	void draw();

};