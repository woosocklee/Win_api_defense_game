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
	//스포너. 총알 스폰되게 함. (spawnpos, 0)에서 스폰됨.
	//
	//
};

