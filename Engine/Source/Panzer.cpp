#pragma once
#include "Shader.h"
#include "Engine.h"
#include "Defines.h"
#include <Panzer.h>

Panzer::Panzer(int coordX0, int coordY0, int velocity0, int direction0) {
	coordX = coordX0;
	coordY = coordY0;
	velocity = velocity0;
	direction = direction0;
	IsAlive = 1;
	cooldown = std_cooldown;
}
	

void Panzer :: update() {

}
void Panzer::draw() {

}
void Panzer::logic() {

}