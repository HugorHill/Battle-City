
#pragma once
#include "MemoryManager.h"
#include "Terrain.h"

class Bullet : public GameObject {
protected:
	int condition; // состояние 1 летит, 0 - уничтожить
	int velocity; 
	int direction; //0 - up, 1 - right, 2 - down, 3 - left
	int coordX;
	int coordY;
	
public:
	Bullet(void* p) ;
	void init(void *p) ;
	void update() ;
	void logic();
	void draw();

};