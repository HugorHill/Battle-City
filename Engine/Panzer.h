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
	static double std_cooldown;	
	static void* map; // ��������� �� �����, ������������ � ����
	GLuint texture;
	public:
		Panzer() {};
		static double time; // ����� ����� �������
		Panzer(void*p) { init(p); }; //� ����� ������ � ���� ���������� ������ ������� ������
		int getX() { return coordX; }
		int getY() { return coordY; }
		void init(void* p) {  }
		void draw() ;
		void update();
		virtual void logic() = 0;
		double GetCooldown();
		int IsAlive; // ��������� 1 ���, 0- ����������
		void Shoot();

};