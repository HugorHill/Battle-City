#pragma once
#include "MemoryManager.h"
#include "Engine.h"
#include <vector>
class Panzer : public GameObject {
	protected:
	int coordX;
	int coordY;
	int velocity;
	int direction; //����������� 0-up, 1-right, 2-down, 3-left
	int IsAlive; // ��������� 1 ���, 0- ����������
	double cooldown;
	static double std_cooldown;	
	static GLFWwindow* window;
	static void* map; // ��������� �� �����, ������������ � ����

	public:
		static double time; // ����� ����� �������
		Panzer(void*p) { init(p); }; //� ����� ������ � ���� ���������� ������ ������� ������
		Panzer(int x, int y, int vel, int dir) ;
		void init (void* p) ;
		void draw() {};
		void update();
		virtual void logic() = 0;
		double GetCooldown();
		void Shoot();

};