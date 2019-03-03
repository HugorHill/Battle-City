#pragma once
#include "Panzer.h"

class PanzerPlayer : public Panzer {
public:
	PanzerPlayer() {};
	PanzerPlayer(float x,float y, int dir, float vel,void* _p,void* _map);
	void logic();
	void gg() ;
};