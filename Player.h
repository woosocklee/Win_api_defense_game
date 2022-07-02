#pragma once
#include "Vector2D.h"
#include "Missile.h"
#include <string>
class Player
{
private:
	std::string name;
	int HP;
	Vector2D missileSpawnPoint;
	Vector2D missileDirection;
	Vector2D TurretCurpos;
	int score;
	
public:
	Player();
	~Player();
	Missile shotmissile();
	int getHP();
	void setHP(int newhp);
	int getscore();
	void setscore(int score);
	void update();
	void draw();
	//��Ŭ���� �̻��� �߻�
	//���콺 �����͸� ���󰡸鼭 �߻��� �� �ְ� �ϱ�
	//a�� d�� �� ������ ������ �� �ְ� �ϱ�. �ӵ� �ֱ�.
	//���� ���� ����ϱ�
	//ü�� ��� ������ ����ϰ�, ���� ���ǿ� ���� ������� ���� �����ϰ� ���� �÷��ֱ�.
	//�÷��̾��� ���̷����� y���� +�� ���� �ʰ� �ϱ�.
};