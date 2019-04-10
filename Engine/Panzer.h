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
		int num_texture;//����� �������� 0-31 � ������, 0-7 � ����
		float stun_time; // ����� � �����
		std::vector <GLuint> texture;
		//~Panzer() { _ptr(engine,Engine)->mm.delTexture(texture); };
		float time_turn;
		int getDir();
		float getVel();
		float immortality_time; //���������� ����� ����������
		static void* map; 	// ��������� �� �����, ������������ � ����
		static double time; // ����� ����� �������
		Panzer() { init(); }; //� ����� ������ � ���� ���������� ������ ������� ������
		~Panzer();
		float getX() { return coordX; }
		float getY() { return coordY; }
		void init() {  }
		void draw() ;
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