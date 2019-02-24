#pragma once
#include "Panzer.h"

class PanzerPlayer : public Panzer {
public:
	PanzerPlayer() {};
	PanzerPlayer(int x,int y, int vel, int dir,void* _p,void* _map);
	void logic();
};