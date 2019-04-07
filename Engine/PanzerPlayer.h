#pragma once
#include "Panzer.h"

class PanzerPlayer : public Panzer {
private:
	int level;
	


public:
	void del();
	PanzerPlayer() {};
	PanzerPlayer(float x,float y, int dir, float vel,void* _map);
	void logic();
	int getlevel() { return level; }
	void gg() ;
	void upgrade(int type) ;
};