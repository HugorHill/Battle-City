#pragma once
#include <MemoryManager.h>
#include <Terrain.h>

Class Bullet : public GameObject{
private :
	int condition; // ��������� 1 - ����������, 0 - ��������� ����������
	int velocity; //0 - up, 1 - right, 2 - down, 3 - left
	int direction;
	Bullet(int direction)

}