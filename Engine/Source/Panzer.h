#pragma once
#include <MemoryManager.h>
#include <Terrain.h>

class Panzer : public GameObject {
	protected :
		int coordX;
		int coordY;
		int velocity; //��������
		int direction;//0-up, 1-right, 2-down, 3-left
		double cooldown; //����������� �����
		int IsAlive;// 1- ��� 0 -����
		static int std_cooldown;


	public:
		Panzer(int coordX0, int coordY0, int velocity0, int direction0) {};		
		Panzer(int coordX, int coordY) {};
		~Panzer() {};
		void GameObject : init(void* p) ;
		void GameObject:  draw();
		void GameObject : logic();
		void GameObject : update();

	
};
