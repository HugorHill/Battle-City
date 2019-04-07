#pragma once
#include "MemoryManager.h"
#include "RenderManager.h"
#include "Engine.h"
#include "PanzerPlayer.h"
#include <vector>
class Bonus : public GameObject {
private:
	double coordX;
	double coordY;
	int type;
	double lifetime;
	
	
public:
	GLuint texture;
	Bonus() {};
	Bonus(double x, double y, int type);
	static double time;
	void del(PanzerPlayer*); // ��������, ����� �������� ����
	void update ();
	void draw();
	void logic() {};
	void init() {};
	int get_type() { return type; }
	double getX() { return coordX; }
	double getY() { return coordY; }
	double getlifetime(){ return lifetime; }
};
/* 1 ������� (������) 2 ��������� ����� (����) 3 ����� ���� ������ (�������)
 4 ������������� ������ (����) 5 ������ ����� (������) 6 ����� (����������)*/