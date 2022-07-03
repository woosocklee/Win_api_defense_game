#pragma once
#include "Vector2D.h"
class Missile
{
private:
	Vector2D curPos;
	Vector2D speed;
	double radius = 10;
	bool state;
public:
	enum class Mtype
	{
		Enemy = 1,
		Player = 2
	};
	Mtype missileType;
	Missile(const Vector2D& spawnp, const Vector2D& speed, Mtype mtype);
	~Missile();
	bool overlap(const Missile& otherM);
	int overlapwall(int x, int y);
	bool getmissileType();
	bool getstate() const;
	void setstate(bool newstate);
	void update(float dt);
	void draw(HDC hdc);

	//º®°ú ´êÀ¸¸é ÆÄ±«
	//ÃÑ¾Ë³¢¸® ´êÀ¸¸é Á¡¼ö È¹µæ
};

void drawcircle(HDC hdc, Vector2D center, int radius);
void Gdi_Draw_Arrow(HDC hdc, int x, int y);