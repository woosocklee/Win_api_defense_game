#pragma once
#include "Vector2D.h"
class Missile
{
	Vector2D curPos;
	Vector2D speed;
	double radius = 10;

public:
	Missile();
	Missile(const Vector2D& spawnp, const Vector2D& speed);
	~Missile();
	bool overlap(const Missile& otherM);
	int overlapwall(int x, int y);

	void update();

	//���� ������ �ı�
	//�Ѿ˳��� ������ ���� ȹ��
};

