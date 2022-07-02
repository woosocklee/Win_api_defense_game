#include "pch.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

missile* Player::shotmissile()
{
    missile* shot = new missile(this->missileSpawnPoint, this->MissileDirection);
    return shot;
}

void Player::setHP(int newhp)
{
}

void Player::update()
{
}
