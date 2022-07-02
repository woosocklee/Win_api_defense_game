#include "pch.h"
#include "Player.h"
#include "framework.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


Player::Player()
{
    this->HP = 10;
    this->score = 0;
}

Player::~Player()
{
}

Missile Player::shotmissile()
{
    Missile shot = Missile(this->missileSpawnPoint, this->missileDirection, Missile::Mtype::Player);
    return shot;
}

int Player::getHP()
{
    return this->HP;
}

void Player::setHP(int newhp)
{
    this->HP = newhp;
}

int Player::getscore()
{
    
    return this->score;
}

void Player::setscore(int score)
{
    this->score = score;
}

void Player::update()
{
    //마우스 포인터 위치 받아와서 그 좌표에 맞게 missileSpawnPoint, missileDirection 조정해주기.
    //이동한만큼 TurretCurpos 조정해주기.

    if (this->HP == 0)
    {
        return;//체력 0되면 사망처리하기.
    }
}

void Player::draw(HDC hdc)
{
    Gdi_Draw(hdc, this->TurretCurpos.x, this->TurretCurpos.y); // 반원 그림
    Vector2D centervec = (this->TurretCurpos + this->missileSpawnPoint) / 2;
    Gdi_barrel(hdc, centervec.x , centervec.y , atan2(this->missileDirection.x, this->missileDirection.y) * 180 / M_PI); //포신 그리기.
}

std::wstring Player::getname() const
{
    return this->name;
}

void Player::setname(const std::wstring newname)
{
    this->name = newname;
}

void Gdi_Init(ULONG_PTR& g_GdiToken)
{
    GdiplusStartupInput gpsi;
    GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_Draw(HDC hdc, int x, int y)
{
    Graphics graphics(hdc);
    Image img((WCHAR*)L"images/halfarc.png");
    int w = img.GetWidth();
    int h = img.GetHeight();
    graphics.DrawImage(&img, x - (w / 2), y - h, w, h);
}

void Gdi_barrel(HDC hdc, int x, int y, int rot)
{
    Graphics graphics(hdc);
    Image* pImg = nullptr;
    pImg = Image::FromFile((WCHAR*)L"images/barrel.png");
    int xPos = x;
    int yPos = y;
    int w;
    int h;
    if (pImg)
    {
        w = pImg->GetWidth();
        h = pImg->GetHeight();

        Gdiplus::Matrix mat;


        mat.RotateAt((rot % 360), PointF(xPos, yPos));
        graphics.SetTransform(&mat);
        graphics.DrawImage(pImg, xPos-(w/2), yPos - (h/2), w, h);



        mat.Reset();
        graphics.SetTransform(&mat);
    }
}