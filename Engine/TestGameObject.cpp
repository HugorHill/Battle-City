#include "TestGameObject.h"


void TestGameObject::init()
{
	texture = engine->mm.loadTexture("map/explode.png");
};

static float time = 0;
void TestGameObject::draw()
{
	time += 0.025;
	if (time >= 1) time = 0;
	engine->rm.draw_square(texture, 20, { 0,0 }, 0, time, 16);
	engine->rm.render_squares();
};