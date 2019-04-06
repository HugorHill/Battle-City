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
void Map :: destroy_them_all(){
	bots.clear();
}
void Map::stun_them_all() {
	for (auto i : bots) {
		i.stun_time = std_stun_time;
		i.set_cooldown(std_stun_time);
	}
}
void Map::AddBonus(int type) {
	Bonus temp(rand() % (int)map_width, rand() % (int)map_height, type);
	bonuses.push_back(temp);
}
void Map :: init() {
	engine->vm.createVar("hero position", sizeof(glm::vec2));

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
	textures[0] = engine->mm.loadTexture("map/ground.jpg");
	textures[1] = engine->mm.loadTexture("map/grass.jpg");
	textures[2] = engine->mm.loadTexture("map/brick.jpg");
	textures[3] = engine->mm.loadTexture("map/beton.jpg");
	textures[4] = engine->mm.loadTexture("map/water.jpg");
	time = glfwGetTime();
	deltatime = 0;
	
}

void Map :: draw() {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++){
			glm::vec2 pos = { 16 * i - 256 + square_width,16 * j - 256 + square_width };
			glm::vec2 player_pos = { player.getX(),player.getY() };
			engine->rm.draw_square(textures[map[i][j]], square_width*2 , pos);
			if (map[i][j] == 2 || map[i][j] == 3)
				engine->rm.draw_shadow(player_pos, pos);
		}
	}
	for (auto &i : bullets) {
		i.draw();
	}
	for (auto &i : bots) {
		i.draw();
	}
	for (auto &i : bonuses) {
		i.draw();
	}
	player.draw();

	/*
		теперь рисование устроено чуть иначе:
		при вызове функции engine->rm.draw_square(..) RenderManager как бы запомнинает параметры вызова этой функции
		а для рисования уже надо будет вызвать engine->rm.render_squares();
		по сути ты сначала запихиваешь с массив все, что хочешь нарисовать, а потом говоришь: "нарисуй мне все разом"
		эта штука была реализована для ускорения процесса
	*/
	engine->rm.render_squares();
	engine->rm.render_shadows();
}

void Map::logic() {
	player.logic();
	for (auto &i : bots) {
		i.logic();
	}
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		engine->sm.set_cur_scene("main menu");
	}
}
void Map:: destr(float x0, float y0, Bullet* b) {
	int x = (int)(x0 + 256) / 16; // в каком блоке сейчас находится пуля
	int y = (int)(y0 + 256) / 16;
	switch (map[x][y]) {
	case 2: b->del();
		map[x][y] = 0;
		break;
	case 3: b->del();
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
	for (auto &i : bots) { 
		iter.push_back(&i);
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
	Bonus::time = deltatime;
	spawn_timer -= deltatime;
	for (auto &i : bots) {
		i.immortality_time -= deltatime;
		i.time_turn -= deltatime;
	}
	player.immortality_time -= deltatime;

	for (auto &i : bullets) { //столкновения снарядов с картой
		
		i.update();

		float x0 = i.getX();
		float y0 = i.getY();
		destr(x0, y0, &i);
		destr(x0+4, y0, &i);
		destr(x0-4, y0, &i);
		destr(x0, y0+4, &i);
		destr(x0, y0-4, &i);

	}
	
	for ( auto &i : bots) {  //столкновения снарядов с ботами
		for ( auto &j : bullets) { //добавить анимацию уничтожения
			if (abs(j.getX() - i.getX()) <= 1.3*panzer_width &&
				abs(j.getY() - i.getY()) <= 1.3*panzer_width && i.immortality_time<=0)
			{
				i.del();
				j.del();
				frags++;
			}
		}
	}
	for (auto &j : bullets) {

		if (abs(j.getX() - player.getX()) <= 1.3 * panzer_width &&
			abs(j.getY() - player.getY()) <= 1.3 * panzer_width &&  player.immortality_time<=0)
		{
			j.del();
			player.del();
			if (player.IsAlive == 0) {
				player.gg();
			}
			
		}
	}
	for (auto &i : bullets) {
		for (auto &j : bullets) {
			if (i.dist(j) <= max_bullet_dist && i.IsAlive==1 && j.IsAlive==1 && &i!=&j) {
				//можно добавить анимацию взрыва
				i.del();
				j.del();
			}
		
		}
	}
	for (auto &i : bonuses) {
		if (abs(i.getX() - player.getX()) <= bonus_width + panzer_width ||
			abs(i.getY() - player.getY()) <= bonus_width + panzer_width) {
			i.del(&player);
		}
	}
	for (auto it = bullets.begin(); it != bullets.end();) {
		if (it->IsAlive == 0) {
			engine->mm.delTexture(it->texture);
			it=bullets.erase(it);
		}
		else { 
			it++; 
		}
	}
	CountBullet = bullets.size();
	
	for (auto it = bots.begin(); it != bots.end();) {
		if (it->IsAlive == 0) {
			
			engine->mm.delTexture(it->texture);
			it=bots.erase(it);
		}
		else {
			it++;
		}
	}
	CountBot = bots.size();
	int r = rand() % 100;
	if (CountBot < std_max_bots && r < 10 && spawn_timer <=0) {
		PanzerBot p(spawn_botsx[r%3], spawn_botsy[r%3], 0, std_vel,this, r%3+1);
		AddBot(p);
		spawn_timer = std_spawn_cd;
	}
	if (frags == frag1 || frags == frag2 || frags == frag3 || frags == frag4) {
	//if (bonuses.size()<1) {
		r = rand() % 6 + 1;
		AddBonus(r);
	}

}
