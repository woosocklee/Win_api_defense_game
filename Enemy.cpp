#include "pch.h"
#include "Enemy.h"
#include <random>
#include <ctime>

Enemy::Enemy()
{
	spawnPosX = 0;
}

Enemy::~Enemy()
{
}

Missile Enemy::spawnmissile()
{
	Missile enemyshot = Missile({spawnPosX,0}, {0,10}, Missile::Mtype::Enemy);
	return enemyshot;
}

void Enemy::update()
{
	this->setspawnPosX(1200); // 나중에 여기 수정해야함. 값을 어디서 받아와서 쓰게 하기.
}

void Enemy::setspawnPosX(int limitMax)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<double> limitGen(0, limitMax);

	this->spawnPosX = limitGen(rng);

}
