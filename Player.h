#pragma once
#include "Vector2D.h"
#include "missile.h"
#include <string>
class Player
{
private:
	std::string Name;
	int HP;
	Vector2D missileSpawnPoint;
	Vector2D MissileDirection;
	Vector2D TurretCurpos;
	
public:
	Player();
	~Player();
	Missile* shotmissile();
	void setHP(int newhp);
	
	void update();
	//��Ŭ���� �̻��� �߻�
	//���콺 �����͸� ���󰡸鼭 �߻��� �� �ְ� �ϱ�
	//a�� d�� �� ������ ������ �� �ְ� �ϱ�. �ӵ� �ֱ�.
	//���� ���� ����ϱ�
	//ü�� ��� ������ ����ϰ�, ���� ���ǿ� ���� ������� ���� �����ϰ� ���� �÷��ֱ�.
	//�÷��̾��� ���̷����� y���� +�� ���� �ʰ� �ϱ�.
};