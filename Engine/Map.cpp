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
void Map :: init() {
	spawn_botsx.push_back(128);
	spawn_botsx.push_back(-128);
	spawn_botsx.push_back(0);
	spawn_botsy.push_back(192);
	spawn_botsy.push_back(192);
	spawn_botsy.push_back(192);
	spawn_playerx = 64;
	spawn_playery = -192;
	spawn_timer = 0;
	PanzerPlayer temp(spawn_playerx, spawn_playery, 0,0, this);
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
	textures[1] = engine->mm.loadTexture("map/grass.jpg");
	textures[2] = engine->mm.loadTexture("map/brick.jpg");
	textures[3] = engine->mm.loadTexture("map/beton.jpg");
	textures[4] = engine->mm.loadTexture("map/water.jpg");
	time = glfwGetTime();
	deltatime = 0;
	
}

void Map :: draw() {	
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (map[i][j] != 0) {
				engine->rm.drawSquare(textures[map[i][j]], 16,
					{16*i-256+square_width,16*j-256+square_width}, 0);
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
	for (int i = 0; i < CountBot; i++) {
		bots[i].logic();
	}
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		engine->sm.set_cur_scene("main menu");
	}
}
void Map:: destr(float x0, float y0,int i) {
	int x = (int)(x0 + 256) / 16; // в каком блоке сейчас находится пуля
	int y = (int)(y0 + 256) / 16;
	switch (map[x][y]) {
	case 2: bullets[i].del();
		map[x][y] = 0;
		break;
	case 3: bullets[i].del();
		break;
	}
}

void Map :: update() {
	int doupd1 = 1;
	int doupd2 = 1;
	double currentTime = glfwGetTime();    //пересчёт времени производится один раз между вызовами
	deltatime = double(currentTime - time);
	time = currentTime;
	std::vector <Panzer*> iter;
	iter.push_back(&player);	//обработка столкновений на итераторах
	for (int i = 0; i < CountBot; i++) { 
		iter.push_back(&bots[i]);
	}
	for (int i = 0; i < iter.size(); i++) {
		int doupd = 1;
		PanzerBot now(iter[i]->getX(),iter[i]->getY(),iter[i]->getDir(),iter[i]->getVel(),this,1);
		now.update();
		for (int j = 0; j < iter.size(); j++) {  //проверка столкновений танков с танками
			if (j != i && abs(iter[i]->getX() - iter[j]->getX()) <= 2 * panzer_width &&
				abs(iter[i]->getY() - iter[j]->getY()) <= 2 * panzer_width) {
				if (Panzer::dist(&now, iter[j]) <= Panzer::dist(iter[i], iter[j])) {
					doupd = 0;
					iter[i]->time_turn = 0;
				}
			}
		}
		 //проверка столкновений танков с элементами ландшафта
		glm::vec2 right_top, right_bottom, left_top, left_bottom;
		float x0 = now.getX();
		float y0 = now.getY();
		right_top = glm::vec2(x0, y0) + glm::vec2(panzer_width, panzer_width);
		right_bottom = glm::vec2(x0, y0) + glm::vec2(panzer_width, -panzer_width);
		left_top = glm::vec2(x0, y0) + glm::vec2(-panzer_width, panzer_width);
		left_bottom = glm::vec2(x0, y0) + glm::vec2(-panzer_width, -panzer_width);
		int rt = map[(int)((right_top.x + 256) / 16)][(int)((right_top.y + 256) / 16)];
		int rb = map[(int)((right_bottom.x + 256) / 16)][(int)((right_bottom.y + 256) / 16)];
		int lt = map[(int)((left_top.x + 256) / 16)][(int)((left_top.y + 256) / 16)];
		int lb = map[(int)((left_bottom.x + 256) / 16)][(int)((left_bottom.y + 256) / 16)];
		
		if (lb == 2 || lb == 3 || lt == 2 || lt == 3 || rb == 2 || rb == 3 || rt == 2 || rt == 3) {
			doupd = 0;
			iter[i]->time_turn = 0;

		}
		if (doupd == 1) {
			iter[i]->update();
		}

	}
	
	Panzer::time = deltatime;
	Bullet::time = deltatime;
	spawn_timer -= deltatime;
	for (int i = 0; i < CountBot; i++) {
		bots[i].immortality_time -= deltatime;
		bots[i].time_turn -= deltatime;
	}
	player.immortality_time -= deltatime;

	for (int i = 0; i < CountBullet; i++) { //столкновения снарядов с картой
		bullets[i].update();

		float x0 = bullets[i].getX();
		float y0 = bullets[i].getY();
		destr(x0, y0, i);
		destr(x0+4, y0, i);
		destr(x0-4, y0, i);
		destr(x0, y0+4, i);
		destr(x0, y0-4, i);

	}
	
	for (int i = 0; i < CountBot; i++) {  //столкновения снарядов с ботами
		for (int j = 0; j < CountBullet && bots[i].immortality_time <= 0; j++) { //добавить анимацию уничтожения
			if (abs(bullets[j].getX() - bots[i].getX()) <= 1.3*panzer_width &&
				abs(bullets[j].getY() - bots[i].getY()) <= 1.3*panzer_width)
			{
				bullets[j].del();
				bots[i].del();
			}
		}
	}
	for (int j = 0; j < CountBullet && player.immortality_time <= 0; j++) {
		if (abs(bullets[j].getX() - player.getX()) <= 1.3 * panzer_width &&
			abs(bullets[j].getY() - player.getY()) <= 1.3 * panzer_width)
		{
			bullets[j].del();
			player.gg();
			
		}
	}
	for (int i = 0; i < CountBullet; i++) {
		for (int j = i+1; j < CountBullet; j++) {
			if (bullets[i].dist(bullets[j]) <= max_bullet_dist) { //можно добавить анимацию взрыва
				bullets[i].del();
				bullets[j].del();
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
	int r = rand() % 100;
	if (CountBot < std_max_bots && r < 10 && spawn_timer <=0) {
		PanzerBot p(spawn_botsx[r%3], spawn_botsy[r%3], 0, std_vel,this, r%3+1);
		AddBot(p);
		spawn_timer = std_spawn_cd;
	}
}