#pragma once
#include "MemoryManager.h"
#include "RenderManager.h"
#include "Engine.h"
#include "PanzerPlayer.h"
#include <vector>
class Explosion : public GameObject {
public:
	float lifetime;
	float coordX;
	float coordY;
	void* map;
	void draw();
	Explosion(float x, float y, void* map_);
	void init(){};
	void logic() {};
	void update() {};
};