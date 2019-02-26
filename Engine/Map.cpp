#pragma once
#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>
void Map :: AddBot(PanzerBot p) {
	bots.push_back(p);
	CountBot++;
}
void Map::AddBullet(Bullet p) {
	bullets.push_back(p);
	CountBullet++;
}
double Map::GetTime(){
	return deltatime;
}
void Map :: init(void* _p) {
	engine = _p;
	PanzerPlayer temp(0, 0, 0,0,_p, this);
	player = temp;
	CountBot = 0;
	CountBullet = 0;
	std::ifstream in;
	in.open("map/Map1.txt");
	for (int i = 0; i < 32; i++) {
		std::string s;
		getline(in, s);
		for (int j = 0; j < 32; j++) {
			map[i][j] = s[j] - '0';
		}
	}
	
	textures.resize(5);
	textures.reserve(5);
	textures[1] = _ptr(engine, Engine)->mm.loadTexture("map/grass.jpg");
	textures[2] = _ptr(engine, Engine)->mm.loadTexture("map/brick.jpg");
	textures[3] = _ptr(engine, Engine)->mm.loadTexture("map/beton.jpg");
	textures[4] = _ptr(engine, Engine)->mm.loadTexture("map/water.jpg");
	time = glfwGetTime();
	deltatime = 0;
	
}

void Map :: draw() {	
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (map[i][j] != 0) {
				_ptr(engine, Engine)->rm.drawSquare(textures[map[i][j]], 16, {16*i-256+8,16*j-256+8}, 0);
			}

		}
	}
	for (int i = 0; i < CountBullet; i++) {
		bullets[i].draw();
	}
	for (int i = 0; i < CountBot; i++) {
		bots[i].draw();
	}
	player.draw();
}

void Map::logic() {
	player.logic();
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		_ptr(engine, Engine)->set_current_scene(0);
	}
}


void Map :: update() {
	double currentTime = glfwGetTime();    //пересчЄт времени производитс€ один раз между вызовами
	deltatime = double(currentTime - time);
	time = currentTime;
	
	Panzer::time = deltatime;
	Bullet::time = deltatime;
	player.update();
	for (int i = 0; i < CountBullet; i++) {
		bullets[i].update();
	
		int x = (bullets[i].getX() + 256) / 16; // в каком блоке сейчас находитс€ пул€
		int y = (bullets[i].getY() + 256)/ 16;
		switch (map[x][y]) {
		case 2: bullets[i].del();
			map[x][y] = 0;
			break;
		case 3: bullets[i].del();
			break;
		}
	}
	for (int i = 0; i < CountBot; i++) {
		bots[i].logic();  //внутри этой функции провер€ютс€ столкновени€ со стенами и поведение бота
		bots[i].update();
	}
	for (int i = 0; i < CountBot; i++) {
		for (int j = 0; j < CountBullet; j++) {
			if (abs(bullets[j].getX() - bots[i].getX()) <= 12 &&
				abs(bullets[j].getY() - bots[i].getY()) <= 12)
			{
				bullets[j].del();
				bots[i].del();
			}
		}
	}
	std::vector <Bullet> bullets_upd;
	for (int i = 0; i < CountBullet; i++) {
		if (bullets[i].IsAlive == 1) {
			bullets_upd.push_back(bullets[i]);
		}
	}
	CountBullet = bullets_upd.size();
	bullets.resize(CountBullet);
	for (int i = 0; i < CountBullet; i++) {
		bullets[i] = bullets_upd[i];
	}
	std::vector <PanzerBot> bots_upd;
	for (int i = 0; i < CountBot; i++) {
		if (bots[i].IsAlive == 1) {
			bots_upd.push_back(bots[i]);
		}
	}
	CountBot = bots_upd.size();
	bots.resize(CountBot);
	for (int i = 0; i < CountBot; i++) {
		bots[i] = bots_upd[i];
	}

	if (CountBot < 6 && rand() % 100 < 20) {
		PanzerBot p(20, 20, 0, 200, engine, this, 2);
		AddBot(p);
	}

}