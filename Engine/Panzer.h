#pragma once
#include "MemoryManager.h"
#include "RenderManager.h"
#include "Engine.h"
#include <vector>
class Panzer : public GameObject {
	protected:
	float coordX;
	float coordY;
	float velocity;
	int direction; //направление 0-up, 1-right, 2-down, 3-left
	
	double cooldown;
	static double std_cooldown;	
	static void* map; // указатель на карту, используемую в игре
	GLuint texture;
	public:
		Panzer() {};
		static double time; // время между кадрами
		Panzer(void*p) { init(p); }; //у танка игрока и бота отличаются только функции логики
		int getX() { return coordX; }
		int getY() { return coordY; }
		void init(void* p) {  }
		void draw() ;
		void update();
		virtual void logic() = 0;
		double GetCooldown();
		int IsAlive; // состояние 1 жив, 0- уничтожить
		void Shoot();

};