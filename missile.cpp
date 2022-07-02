#include "pch.h"
#include "missile.h"
#include "framework.h"



Missile::Missile(const Vector2D& spawnp, const Vector2D& speed, Mtype mtype)
{
	this->curPos = spawnp;
	this->speed = speed;
	this->missileType = mtype;
}

Missile::~Missile()
{
}

bool Missile::overlap(const Missile& otherM)
{
	if (Vector2D{ this->curPos - otherM.curPos }.getlengthsq() < 400)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Missile::overlapwall(int x, int y)
{
	if (this->curPos.y > y || this->curPos.x > x || this->curPos.x < 0 || this->curPos.y < -10)
	{
		if (this->curPos.y > y && this->missileType == Mtype::Enemy)
		{
			return 1; // Ã¼·Â¹Ù¿¡ ´êÀ½
		}
		else
		{
			return -1; // ÀÏ¹Ý º®¿¡ ´êÀ½.
		}
	}
	else
	{
		return 0; // ¾È´êÀ½.
	}
}

bool Missile::getmissileType()
{
	switch (this->missileType)
	{
	case Mtype::Enemy:
		return true;
		break;
	case Mtype::Player:
		return false;
		break;
	default:
		return false;
		break;
	}
}

bool Missile::getstate() const
{
	return this->state;
}

void Missile::setstate(bool newstate)
{
	this->state = newstate;
}

void Missile::update()
{
	this->curPos.x += this->speed.x;
	this->curPos.y += this->speed.y;
}

void Missile::draw(HDC hdc)
{
	switch (this->missileType)
	{
	case Mtype::Enemy:
		
		break;
	case Mtype::Player:
		drawcircle(hdc, { this->curPos.x,this->curPos.y }, this->radius);
		break;
	default:
		break;
	}
}


void drawcircle(HDC hdc, Vector2D center, int radius)
{
	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}