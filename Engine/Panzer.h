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
	int direction; //����������� 0-up, 1-right, 2-down, 3-left	
	double cooldown;
	double speed_boost;
	int health; // ��������
	

	
	public:
		float stun_time; // ����� � �����
		float swap_time;
		float time_turn;
		int getDir();
		float getVel();
		float immortality_time; //���������� ����� ����������
		static void* map; 	// ��������� �� �����, ������������ � ����
		static double time; // ����� ����� �������
		Panzer() { init(); }; //� ����� ������ � ���� ���������� ������ ������� ������
		float getX() { return coordX; }
		float getY() { return coordY; }
		void init() {  }
		virtual void draw()=0 ;
		void del();
		void update();
		virtual void logic() =0;
		double GetCooldown();
		int IsAlive; // ��������� 1 ���, 0- ����������
		void Shoot();
		void CancelMove();
		void set_cooldown(float cd) { cooldown = cd;}
		static float dist(Panzer* a,Panzer* b);
		int gethealth() { return health; }
};