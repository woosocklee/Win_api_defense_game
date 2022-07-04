#include "pch.h"
#include "Shield.h"

#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


Shield::Shield(bool ok, const Vector2D& cvec)
{
	curVec = cvec;
	ok = true;
}

void Shield::draw(HDC hdc, int x, int y)
{

	if (this->ok)
	{
		Gdi_Draw_full_hpbar(hdc, x, y); // rect에서 bottom값 받아오게 하기.
	}
	else
	{
		Gdi_Draw_empty_hpbar(hdc, x, y);
	}
}

void Shield::update()
{
}

Vector2D Shield::getcurVec()
{
	return this->curVec;
}

void Shield::setcurVec(const Vector2D& newvec)
{
	this->curVec = newvec;
}

void Shield::Gdi_Draw_full_hpbar(HDC hdc, int x, int y)
{
	Graphics graphics(hdc);
	Image img((WCHAR*)L"Image/fullhp.png");
	int w = img.GetWidth();
	int h = img.GetHeight();
	graphics.DrawImage(&img, x + w + 20, y - h, w, h);
}

void Shield::Gdi_Draw_empty_hpbar(HDC hdc, int x, int y)
{
	Graphics graphics(hdc);
	Image img((WCHAR*)L"Image/emptyhp.png");
	int w = img.GetWidth();
	int h = img.GetHeight();
	graphics.DrawImage(&img, x + w + 20, y - h, w, h);
}