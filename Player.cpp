#include "pch.h"
#include "Player.h"
#include "framework.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


Player::Player(const RECT R)
{

    this->score = 0;
    this->TurretCurpos = {double((R.left + R.right)/2) , double(R.top + 50) };
    this->dead = false;
}

Player::~Player()
{
}

Missile Player::shotmissile()
{
    Missile shot = Missile(this->missileSpawnPoint, this->missileDirection * 40, Missile::Mtype::Player);
    return shot;
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

}

void Player::draw(HDC hdc)
{
    Gdi_DrawPlayer(hdc, this->TurretCurpos.x, this->TurretCurpos.y); // 반원 그림
    Vector2D centervec = (this->TurretCurpos + this->missileSpawnPoint) / 2;

    double radian = atan2(this->missileDirection.x, -1 * this->missileDirection.y) * 180 / M_PI;

    if (radian < -90)
    {
        radian = -90;
    }
    else if (radian > 90)
    {
        radian = 90;
    }
    
    Gdi_barrel(hdc, centervec.x , centervec.y - 10 , radian); //포신 그리기.
}

std::wstring Player::getname() const
{
    return this->name;
}

void Player::setname(const std::wstring newname)
{
    this->name = newname;
}

void Player::setmissileDirection(Vector2D mousepoint)
{
    Vector2D tempvec = mousepoint - this->TurretCurpos;
    this->missileDirection = tempvec.normalize();
    this->missileSpawnPoint = this->TurretCurpos + (this->missileDirection * 20);
}

void Player::setTCurPos(Vector2D pos)
{
    this->TurretCurpos = pos;
}

bool Player::getdead()
{
    return this->dead;
}

void Player::setdead(bool newdead)
{
    this->dead = newdead;
}


void Player::Gdi_DrawPlayer(HDC hdc, int x, int y)
{
    Graphics graphics(hdc);
    Image img((WCHAR*)L"Image/halfarc.png");
    
    int w = img.GetWidth();
    int h = img.GetHeight();
    graphics.DrawImage(&img, x - (w / 20), y - h / 10, w / 10, h / 10);
}

void Player::Gdi_barrel(HDC hdc, int x, int y, int rot)
{
    Graphics graphics(hdc);
    Image* pImg = nullptr;
    pImg = Image::FromFile((WCHAR*)L"Image/barrel.png");
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