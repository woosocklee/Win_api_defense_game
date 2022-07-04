#pragma once
#include "Vector2D.h"
#include "Missile.h"
#include <string>
#include <vector>
class Player
{
private:
	std::wstring name;
	Vector2D missileSpawnPoint;
	Vector2D missileDirection;
	Vector2D TurretCurpos;
	int score;
	
public:
	Player(const RECT R);
	~Player();
	Missile shotmissile();
	int getscore();
	void setscore(int score);
	void update();
	void draw(HDC hdc);
	std::wstring getname() const; 
	void setname(const std::wstring newname);
	void setmissileDirection(Vector2D mousepoint);
	void setTCurPos(Vector2D pos);
	//��Ŭ���� �̻��� �߻�
	//���콺 �����͸� ���󰡸鼭 �߻��� �� �ְ� �ϱ�
	//a�� d�� �� ������ ������ �� �ְ� �ϱ�. �ӵ� �ֱ�.
	//���� ���� ����ϱ�
	//ü�� ��� ������ ����ϰ�, ���� ���ǿ� ���� ������� ���� �����ϰ� ���� �÷��ֱ�.
	//�÷��̾��� ���̷����� y���� +�� ���� �ʰ� �ϱ�.
};
void Gdi_DrawPlayer(HDC hdc, int x, int y);
void Gdi_barrel(HDC hdc, int x, int y, int rot);