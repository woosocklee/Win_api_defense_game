#pragma once
#include "Vector2D.h"
class Shield
{
private:
	Vector2D curVec;
	

public:
	bool ok;
	Shield(bool ok, const Vector2D& cvec);
	void draw(HDC hdc, int x, int y);
	void update();
	Vector2D getcurVec();
	void setcurVec(const Vector2D& newvec);
	void Gdi_Draw_full_hpbar(HDC hdc, int x, int y);
	void Gdi_Draw_empty_hpbar(HDC hdc, int x, int y);
};

