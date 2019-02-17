#pragma once
#include "MemoryManager.h"
#include "Engine.h"
#include <vector>
class Panzer : public GameObject {
	protected:
	int coordX;
	int coordY;
	int velocity;
	int direction; //направление 0-up, 1-right, 2-down, 3-left
	int IsAlive; // состояние 1 жив, 0- уничтожить
	double cooldown;
	static double std_cooldown;	
	static GLFWwindow* window;
	static void* map; // указатель на карту, используемую в игре

	public:
		static double time; // время между кадрами
		Panzer(void*p) { init(p); }; //у танка игрока и бота отличаются только функции логики
		Panzer(int x, int y, int vel, int dir) ;
		void init (void* p) ;
		void draw() {};
		void update();
		virtual void logic() = 0;
		double GetCooldown();
		void Shoot();

};