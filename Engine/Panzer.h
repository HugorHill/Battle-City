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
	double speed_boost;
	int health; // здоровье
	

	
	public:
		int num_texture;//номер текстуры 0-31 у плеера, 0-7 у бота
		float stun_time; // время в стане
		std::vector <GLuint> texture;
		//~Panzer() { _ptr(engine,Engine)->mm.delTexture(texture); };
		float time_turn;
		int getDir();
		float getVel();
		float immortality_time; //оставшееся время бессмертия
		static void* map; 	// указатель на карту, используемую в игре
		static double time; // время между кадрами
		Panzer() { init(); }; //у танка игрока и бота отличаются только функции логики
		~Panzer();
		float getX() { return coordX; }
		float getY() { return coordY; }
		void init() {  }
		void draw() ;
		void del();
		void update();
		virtual void logic() =0;
		double GetCooldown();
		int IsAlive; // состояние 1 жив, 0- уничтожить
		void Shoot();
		void CancelMove();
		void set_cooldown(float cd) { cooldown = cd;}
		static float dist(Panzer* a,Panzer* b);
		int gethealth() { return health; }
};