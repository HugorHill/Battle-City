#pragma once
#include "Panzer.h"

class PanzerBot : public Panzer {
public :
	
	PanzerBot() {};
	void logic() ;
	PanzerBot(float x, float y, int dir, float vel, void*_p, void* _map,int type);
	void del() { IsAlive = 0; }

};