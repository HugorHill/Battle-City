#include "Bullet.h"
#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
#include "Map.h"
float Bullet::BulletSpeed = std_BulletSpeed;
double Bullet::time = 0;



Bullet::Bullet(int x, int y,  int dir,double boost, void* map_) {
	coordX = x;
	coordY = y;	
	direction = dir;
	speed_boost = boost;
	IsAlive = 1;
	map = map_;
}

void Bullet :: update() {
	if (direction == 0) {
		coordY += speed_boost*BulletSpeed * time;
	}
	if (direction == 1) {
		coordX+= speed_boost * BulletSpeed * time;
	}
	if (direction == 2) {
		coordY -= speed_boost * BulletSpeed * time;
	}
	if (direction == 3) {
		coordX -= speed_boost * BulletSpeed * time;
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
	engine->rm.draw_square(_ptr(map,Map)->bullet_texture, bullet_width, pos, angel);

}
float Bullet::dist(Bullet a) {
	float dx = coordX - a.getX();
	float dy = coordY - a.getY();
	return sqrt(dx*dx + dy * dy);
}
bool Bullet ::operator < ( Bullet p) const {
	return (coordX < p.coordX);
}
