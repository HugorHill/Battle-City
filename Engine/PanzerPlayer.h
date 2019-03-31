#pragma once
#include "Panzer.h"

class PanzerPlayer : public Panzer {
private:
	int level;

public:
	PanzerPlayer() {};
	PanzerPlayer(float x,float y, int dir, float vel,void* _map);
	void logic();
	void gg() ;
	void upgrade(int type) ;
};