#pragma once
#include "Map.h"
#include <fstream>
#include <string>
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
void Map :: init(void* p) {


}
Map::Map(void* _p, void * _map) {
	PanzerPlayer temp(0, 0, std_vel, 0, _p, _map);
	player = temp;
	bots.clear();
	bullets.clear();
	CountBot = 0;
	CountBullet = 0;
	std::ifstream in;
	in.open("map/map1.txt");
	for (int i = 0; i < 32; i++) {
		std::string s;
		getline(in, s);
		for (int j = 0; j < 32; j++) {
			map[i][j] = s[j]-'0';
		}
	}
	textures[1] = _ptr(engine, Engine)->mm.loadTexture("map/grass", true);
	textures[2] = _ptr(engine, Engine)->mm.loadTexture("map/brick", true);
	textures[3]=_ptr(engine, Engine)->mm.loadTexture("map/beton", true);
	textures[4] = _ptr(engine, Engine)->mm.loadTexture("map/water", true);
	time = glfwGetTime();
	deltatime = 0;

}
void Map :: draw() {
	
	for (int i = 0; i < CountBullet; i++) {
		bullets[i].draw();
	}
	for (int i = 0; i < CountBot; i++) {
		bots[i].draw();
	}
	player.draw();
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (map[i][j] != 0) {
				_ptr(engine, Engine)->rm.drawSquare(textures[map[i][j]], 16, {16*i-256,16*j-256}, 0);
			}

		}
	}
}

void Map::logic() {}


void Map :: update() {
	double currentTime = glfwGetTime();    //�������� ������� ������������ ���� ��� ����� ��������
	deltatime = double(currentTime - time);
	time = currentTime;
	Panzer::time = deltatime;
	Bullet::time = deltatime;
	for (int i = 0; i < CountBullet; i++) {
		bullets[i].update();
		int x = (bullets[i].getX() + 256) / 16; // � ����� ����� ������ ��������� ����
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
		bots[i].logic();  //������ ���� ������� ����������� ������������ �� ������� � ��������� ����
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
	bullets.clear();
	CountBullet = bullets_upd.size();
	bullets = bullets_upd; 
	std::vector <PanzerBot> bots_upd;
	for (int i = 0; i < CountBot; i++) {
		if (bots[i].IsAlive == 1) {
			bots_upd.push_back(bots[i]);
		}
	}
	bots.clear();
	CountBot = bots_upd.size();
	bots=bots_upd;
}