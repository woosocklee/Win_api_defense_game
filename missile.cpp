#include "pch.h"
#include "missile.h"

Missile::Missile()
{
	this->curPos = { -1000,0 };
	this->speed = { 0,0 };
}

Missile::Missile(const Vector2D& spawnp, const Vector2D& speed)
{
	this->curPos = spawnp;
	this->speed = speed;
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
		if (this->curPos.y > y)
		{
			return -1; // ü�¹ٿ� ����
		}
		else
		{
			return 0; // �Ϲ� ���� ����.
		}
	}
	else
	{
		return 1; // �ȴ���.
	}
}

void Missile::update()
{
	this->curPos.x += this->speed.x;
	this->curPos.y += this->speed.y;
}
