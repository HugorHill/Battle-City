#include "Map.h"
void Map :: AddBot(PanzerBot p) {
	bots.push_back(p);
	CountBot++;
}
void Map::AddBullet(Bullet p) {
	bullets.push_back(p);
	CountBullet++;
}
double Map::GetTime(){
	return deltatime;
}
void Map :: init(void* p) {


}
void Map :: draw() {

}
void Map :: logic() {

}
void Map :: update() {
	double currentTime = glfwGetTime();    //пересчёт времени производится один раз между вызовами
	deltatime = double(currentTime - time);
	time = currentTime;
	Panzer::time = deltatime;


}