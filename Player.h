#pragma once
#include "Vector2D.h"
#include <string>
class Player
{
private:
	std::string Name;
	int HP;
	Vector2D missileSpawnPoint;
	Vector2D MissileDirection;
	Vector2D TurretCurpos;

	//��Ŭ���� �̻��� �߻�
	//���콺 �����͸� ���󰡸鼭 �߻��� �� �ְ� �ϱ�
	//a�� d�� �� ������ ������ �� �ְ� �ϱ�. �ӵ� �ֱ�.
	//���� ���� ����ϱ�
	//ü�� ��� ������ ����ϰ�, ���� ���ǿ� ���� ������� ���� �����ϰ� ���� �÷��ֱ�.
};