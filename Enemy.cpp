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

missile* Enemy::spawnmissile()
{
	missile* enemyshot = new missile({spawnPosX,0}, {0,10});
	return enemyshot;
}

void Enemy::update()
{
	this->setspawnPosX();
}

void Enemy::setspawnPosX(int limitMax)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<double> limitGen(0, limitMax);

	this->spawnPosX = limitGen(rng);

}
