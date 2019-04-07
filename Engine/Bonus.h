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
	void del(PanzerPlayer*); // вызываем, когда подобрал танк
	void update ();
	void draw();
	void logic() {};
	void init() {};
	int get_type() { return type; }
	double getX() { return coordX; }
	double getY() { return coordY; }
	double getlifetime(){ return lifetime; }
};
/* 1 апгрейд (звезда) 2 добавл€ет жизнь (танк) 3 взрыв всех врагов (граната)
 4 останавливает врагов (часы) 5 защита штаба (лопата) 6 каска (неу€звимый)*/