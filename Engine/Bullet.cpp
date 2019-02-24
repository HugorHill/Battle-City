#include "Bullet.h"
#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
//you should init static variables
int Bullet::BulletSpeed = 1;
double Bullet::time = 0;



Bullet::Bullet(int x, int y,  int dir) {
	coordX = x;
	coordY = y;	
	direction = dir;
	IsAlive = 1;
	texture = _ptr(engine, Engine)->mm.loadTexture("map/panzer2", true);
}
void Bullet :: init(void *p) {

}
void Bullet :: update() {
	if (direction == 0) {
		coordY += BulletSpeed * time;
	}
	if (direction == 1) {
		coordX+= BulletSpeed * time;
	}
	if (direction == 2) {
		coordY -= BulletSpeed * time;
	}
	if (direction == 3) {
		coordX -= BulletSpeed * time;
	}

}
void Bullet :: del(){
	IsAlive = 0;
}
void Bullet :: logic() {

}
void Bullet :: draw() {
	glm::vec2 pos = { coordX,coordY };
	float angel;
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
	_ptr(engine, Engine)->rm.drawSquare(texture, 4, pos, angel);
}