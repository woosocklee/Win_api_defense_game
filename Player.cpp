#include "pch.h"
#include "Player.h"
#include "framework.h"

Player::Player()
{
    this->HP = 10;
    this->score = 0;
}

Player::~Player()
{
}

Missile Player::shotmissile()
{
    Missile shot = Missile(this->missileSpawnPoint, this->missileDirection, Missile::Mtype::Player);
    return shot;
}

int Player::getHP()
{
    return this->HP;
}

void Player::setHP(int newhp)
{
    this->HP = newhp;
}

int Player::getscore()
{
    
    return this->score;
}

void Player::setscore(int score)
{
    this->score = score;
}

void Player::update()
{
    //ü�� 0�Ǹ� ���ó���ϱ�.
}

void Player::draw()
{
    
}
