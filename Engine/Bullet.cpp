#include "Bullet.h"
#include "Terrain.h"

Bullet::Bullet(int x, int y,  int dir) {
	coordX = x;
	coordY = y;	
	direction = dir;
	IsAlive = 1;
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
void Bullet :: logic() {

}
void Bullet :: draw() {

}