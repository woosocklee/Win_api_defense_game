#pragma once
#include "Vector2D.h"
#include "missile.h"
class Enemy
{
private:
	double spawnPosX;

public:
	Enemy();
	~Enemy();
	Missile spawnmissile();
	Missile update(const RECT windowsize);
	void setspawnPosX(int limitMax);
	//������. �Ѿ� �����ǰ� ��. (spawnpos, 0)���� ������.
	//
	//
};

