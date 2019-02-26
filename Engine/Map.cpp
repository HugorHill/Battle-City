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
				_ptr(engine, Engine)->rm.drawSquare(textures[map[i][j]], 16,
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
	if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		_ptr(engine, Engine)->set_current_scene(0);
	}
}


void Map :: update() {
	int doupd1 = 1;
	int doupd2 = 2;
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
		Panzer now = *iter[i];
		now.update();
		for (int j = 0; j < iter.size(); j++) {  //проверка столкновений с танками
			if (j != i && abs(iter[i]->getX() - iter[j]->getX()) <= 2 * panzer_width &&
				abs(iter[i]->getY() - iter[j]->getY()) <= 2 * panzer_width) {
				if (Panzer::dist(&now, iter[j]) <= Panzer::dist(iter[i], iter[j])) {
					doupd = 0;
				}
			}
		}
		 //проверка столкновений с элементами ландшафта
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
		}
		if (doupd == 1) {
			iter[i]->update();
		}

	}
	
	Panzer::time = deltatime;
	Bullet::time = deltatime;
	/*PanzerPlayer now = player;
	now.update();

	glm::vec2 right_top, right_bottom, left_top, left_bottom; //столкновения с ландшафтом
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
		doupd1 = 0;
	}
	for (int i = 0; i < CountBot; i++) { //можно доделать под 2 игроков
		if (abs(bots[i].getX() - player.getX()) <= 2 * panzer_width &&
			abs(bots[i].getY() - player.getY()) <= 2 * panzer_width) {
			if ( Panzer::dist(&now, &bots[i]) <= Panzer::dist(&player, &bots[i])) {
				doupd1 = 0;
			}
		}

	}
	if (doupd1 == 1) {
		player.update();
	}
	player.logic(); */ //внутри этой функции проверяются столкновения со стенами и поведение бота
	

	/*for (int i = 0; i < CountBot; i++) {
		int doupd = 1;
		for (int j = 0; j < CountBot; j++) {  //проверка столкновений с танками
			if (j != i && abs(bots[i].getX() - bots[j].getX()) <=2*panzer_width &&
				abs(bots[i].getY() - bots[j].getY())<=2*panzer_width) {
				doupd = 0;
			}
		}
		PanzerBot now = bots[i];
		
		bots[i].logic();
		now.update(); //проверка столкновений с элементами ландшафта
		glm::vec2 right_top, right_bottom, left_top, left_bottom;
		float x0 = now.getX();
		float y0 = now.getY();
		right_top = glm::vec2(x0, y0) + glm::vec2(panzer_width, panzer_width);
		right_bottom = glm::vec2(x0,y0) + glm::vec2(panzer_width, -panzer_width);
		left_top = glm::vec2(x0,y0) + glm::vec2(-panzer_width, panzer_width);
		left_bottom = glm::vec2(x0,y0) + glm::vec2(-panzer_width, -panzer_width);
		int rt = map[(int)((right_top.x + 256) / 16)][(int)((right_top.y + 256) / 16)];
		int rb = map[(int)((right_bottom.x + 256) / 16)][(int)((right_bottom.y + 256) / 16)];
		int lt = map[(int)((left_top.x + 256) / 16)][(int)((left_top.y + 256) / 16)];
		int lb = map[(int)((left_bottom.x + 256) / 16) ][(int)((left_bottom.y + 256) / 16)];
		if (glfwGetKey(_ptr(engine, Engine)->getWindow(), GLFW_KEY_R) == GLFW_PRESS) {
			std::cout << rt << " " << rb << " " << lt << " " << lb << std::endl;
		}
		if (lb == 2 || lb == 3 || lt == 2 || lt == 3 || rb == 2 || rb == 3 || rt == 2 || rt == 3) {
			doupd = 0;
		}	
		if (doupd == 1) {
			bots[i].update();
		}
	}
	*/
	for (int i = 0; i < CountBullet; i++) {
		bullets[i].update();

		int x = (bullets[i].getX() + 256) / 16; // в каком блоке сейчас находится пуля
		int y = (bullets[i].getY() + 256) / 16;
		switch (map[x][y]) {
		case 2: bullets[i].del();
			map[x][y] = 0;
			break;
		case 3: bullets[i].del();
			break;
		}
	}
	
	for (int i = 0; i < CountBot; i++) {
		for (int j = 0; j < CountBullet; j++) {
			if (abs(bullets[j].getX() - bots[i].getX()) <= panzer_width &&
				abs(bullets[j].getY() - bots[i].getY()) <= panzer_width)
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