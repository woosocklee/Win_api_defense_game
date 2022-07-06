#include "pch.h"
#include "Gamemanager.h"
#include <algorithm>
#include <string>


#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


// 시작 창
//1. 아이디 입력창을 띄워 아이디 입력받기.
//2. 버튼/엔터 누르기 중에 구현 쉬운거로 입력받으면 그걸 플레이어 아이디 스트링에 박고 게임 시작하기.

// 인 게임
//1. 마우스로 조준하고 좌클릭으로 발사하기 - 총알 발사. 총구에서 발사됨.
//2. a랑 d로 터렛 움직이기 -> 시간되면 하고 아니면 안함.
//3. 총알이 화면 하단에 닿으면 체력이 깎이고, 총알끼리 부딪히면 점수가 올라감.
//4. HP에따라 Defensewall이 활성화된다.
//5. 시간에 따라 적이 스폰한 총알은 아래로 내려가고, 플레이어가 쏜 총알은 자기 방향으로 날아가다가 옆벽에 부딪히면 사라진다.

// 순위 창
//1. 점수 순위를 1~5위까지 보여주고, 플레이어가 순위를 갱신했으면 바꿔주기.
//2. 버튼 누르면 다시 시작창으로.


void Game_manager::Changestage()
{
	switch (this->curStage)
	{
	case Stage::Beginning:

		break;
	case Stage::Gameplay:

		break;
	case Stage::Ranking:

		break;
	default:
		break;
	}
}

void Game_manager::addPmissile(Missile Pm)
{
	this->missiles.push_back(Pm);
}

Game_manager::Game_manager(const RECT r) : windowSize(r), Pturret(r)
{
	if (!missiles.empty())
	{
		missiles = {};
	}
	this->curStage = Stage::Beginning;
	for (int i = 0; i < 10; i++)
	{
		shields.push_back({ true ,{double(r.right/(i+1)),double(r.bottom/(i+1))} });
	}
}

Game_manager::~Game_manager()
{
}

void Game_manager::setwindowSize(RECT window)
{
	this->windowSize = window;

}

Game_manager::Stage Game_manager::getCurStage() const
{
	return this->curStage;
}

void Game_manager::setCurStage(Stage s)
{
	this->curStage = s;
}

void Game_manager::Update()
{
	float dt = timer.GetTime();
	this->accumulatedTime += dt;
	if (this->accumulatedTime > this->spawnrate)
	{
		missiles.push_back(this->enemys.update(this->windowSize));
		this->accumulatedTime = 0;
		spawnrate -= 0.0001;
	}

	this->Changestage();

	for (auto& i : this->missiles)
	{
		i.update(dt);
	}

	for (auto& i : this->missiles)
	{
		//타입이 다른 미사일과의 충돌시 스코어 올리고 제거.
		for (auto& j : this->missiles)
		{
			if (i.getmissileType() != j.getmissileType())
			{
				if (i.overlap(j))
				{
					this->Pturret.setscore(this->Pturret.getscore() + 50);
					i.setstate(false);
					j.setstate(false);
				}
			}
		}

		//벽과의 충돌. 

		switch ((i.overlapwall(this->windowSize.right, this->windowSize.bottom-30)))
		{
		case 1:
			i.setstate(false);
			if (i.getmissileType())
			{
				int fallpoint = int(10 * i.getcurpos().x / this->windowSize.right);
				if (fallpoint >= 0 && fallpoint < 10)
				{
					if (this->shields[fallpoint].ok)
					{
						this->shields[fallpoint].ok = false;
					}
					else
					{
						this->setCurStage(Game_manager::Stage::Ranking);
						//game over
					}
				}

				
			}
			break;
		case -1:
			i.setstate(false);
			break;
		default:
			break;
		}
	}

	this->Pturret.update();

	const auto newEnd = std::remove_if(this->missiles.begin(), this->missiles.end(),
		[](const Missile& m) {return !m.getstate(); }
	);
	this->missiles.erase(newEnd, this->missiles.end());

}

void Game_manager::Draw(HDC hdc)
{
	//미사일 그려주기
	
	HDC outerhdc = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap;


	if (hDoubleBufferImage == nullptr || (this->oldWindowSize.right != this->windowSize.right || this->oldWindowSize.bottom != this->windowSize.bottom) )
	{
		// Create Bitmap Image for Double buffering
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, this->windowSize.right, this->windowSize.bottom);
		for (int i = 0; i < 10; i++)
		{
			shields[i].setcurVec({double((this->windowSize.right/10) *(i-1)) , double(this->windowSize.bottom)});
		}
		this->oldWindowSize = this->windowSize;
	}

	hOldBitmap = (HBITMAP)SelectObject(outerhdc, hDoubleBufferImage);

	FillRect(outerhdc, &this->windowSize, (HBRUSH)GetStockObject(WHITE_BRUSH));

	for (auto& i : this->missiles)
	{
		i.draw(outerhdc);
	}

	//미사일 끝

	//플레이어 그려주기

	this->Pturret.draw(outerhdc);

	//플레이어 그려주기 끝

	//체력바 그려주기

	for (auto& i: shields)
	{
		i.draw(outerhdc, i.getcurVec().x, i.getcurVec().y);
	}
	//플레이어 체력바 끝

	//아이디 그려주기

	Gdi_Draw_name(outerhdc, this->Pturret.getname());


	//점수, 아이디 그리게 해주기.

	Gdi_Draw_score(outerhdc, this->Pturret.getscore());

	//각자 draw하게 해주기.

	BitBlt(hdc, 0, 0, this->windowSize.right, this->windowSize.bottom, outerhdc, 0, 0, SRCCOPY);
	SelectObject(outerhdc, hOldBitmap);
	DeleteObject(outerhdc);
}

void Game_manager::Gdi_Draw_name(HDC hdc, std::wstring name)
{

	Graphics graphics(hdc);
	// >> txt
	SolidBrush brush(Color(255, 255, 255, 255));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF pointF(10.0f, 20.0f);
	graphics.DrawString(&name[0], -1, &font, pointF, &brush);
}

void Game_manager::Gdi_Draw_score(HDC hdc, int score)
{

	Graphics graphics(hdc);
	// >> txt
	SolidBrush brush(Color(255, 255, 0, 0));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF pointF(1000.0f, 20.0f);
	graphics.DrawString(L"Score: ", -1, &font, pointF, &brush);
	pointF = PointF(1168.0f, 20.0f);
	graphics.DrawString(std::to_wstring(score).c_str(), -1, &font, pointF, &brush);
}




void Game_manager::drawDoubleBuffring(/*HWND hWnd,*/ HDC hdc, HBITMAP hBackImage, BITMAP hBitback)
{

	HDC hMemDC;
	HDC hMemDC2;


	HBITMAP hOldBitmap;
	HBITMAP hOldBitmap2;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, hBitback.bmWidth, hBitback.bmHeight);
	}
	

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);

	hMemDC2 = CreateCompatibleDC(hMemDC);
	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
	
	Gdi_Draw_name(hMemDC2, L"woosocklee");



	BitBlt(hMemDC, 0, 0, 1200, 1080, hMemDC2, 0, 0, SRCCOPY);
	SelectObject(hMemDC2, hOldBitmap2);
	DeleteDC(hMemDC2);

	BitBlt(hdc, 0, 0, 1200, 1080, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

