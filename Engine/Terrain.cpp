#include "Terrain.h"
#include "Defines.h"
#include "Engine.h"
//#define GLM_ENABLE_EXPERIMENTAL 1
//#include <glm\gtx\transform.hpp>


void Terrain::init(void* p)
{
	engine = p;
	texture = _ptr(engine, Engine)->mm.loadTexture("sample.jpg");
}

static glm::vec2 pos = glm::vec2(1);
static double time = 0;
static double A = 128;

void Terrain::draw()
{
	time += 0.01;
	pos.x = A*cos(time);
	pos.y = A*sin(time);

	_ptr(engine, Engine)->rm.drawSquare(texture, 256, pos,30);
	_ptr(engine, Engine)->rm.drawText("BATTLE", glm::vec3(0, WINDOW_SIZE_UNITS / 4, 0), true, glm::vec3(0), 1.5, texture);
	_ptr(engine, Engine)->rm.drawText("CITY", glm::vec3(0,WINDOW_SIZE_UNITS/8,0),true,glm::vec3(0),1.5,texture);
}

