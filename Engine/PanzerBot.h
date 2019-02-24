#pragma once
#include "Panzer.h"

class PanzerBot : public Panzer {
public :
	PanzerBot() {};
	void logic() ;
	PanzerBot(int x, int y, int dir, int vel, void*_p, void* _map,int type);
	void del() { IsAlive = 0; }

};