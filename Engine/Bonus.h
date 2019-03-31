#pragma once
#include "MemoryManager.h"
#include "RenderManager.h"
#include "Engine.h"
#include "PanzerPlayer.h"
#include <vector>
class Bonus : public GameObject {
private:
	int coordX;
	int coordY;
	int type;
	double lifetime;
	GLuint texture;
	
public:
	Bonus() {};
	Bonus(int x, int y, int type);
	static double time;
	void del(PanzerPlayer*); // ��������, ����� �������� ����
	void update ();
	void draw();
	void logic() {};
	int get_type() { return type; }



};
/* 1 ������� (������) 2 ��������� ����� (����) 3 ����� ���� ������ (�������)
 4 ������������� ������ (����) 5 ������ ����� (������) 6 ����� (����������)*/