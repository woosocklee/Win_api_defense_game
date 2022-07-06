#include "pch.h"
#include "Gamemanager.h"
#include <algorithm>
#include <string>


#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


// ���� â
//1. ���̵� �Է�â�� ��� ���̵� �Է¹ޱ�.
//2. ��ư/���� ������ �߿� ���� ����ŷ� �Է¹����� �װ� �÷��̾� ���̵� ��Ʈ���� �ڰ� ���� �����ϱ�.

// �� ����
//1. ���콺�� �����ϰ� ��Ŭ������ �߻��ϱ� - �Ѿ� �߻�. �ѱ����� �߻��.
//2. a�� d�� �ͷ� �����̱� -> �ð��Ǹ� �ϰ� �ƴϸ� ����.
//3. �Ѿ��� ȭ�� �ϴܿ� ������ ü���� ���̰�, �Ѿ˳��� �ε����� ������ �ö�.
//4. HP������ Defensewall�� Ȱ��ȭ�ȴ�.
//5. �ð��� ���� ���� ������ �Ѿ��� �Ʒ��� ��������, �÷��̾ �� �Ѿ��� �ڱ� �������� ���ư��ٰ� ������ �ε����� �������.

// ���� â
//1. ���� ������ 1~5������ �����ְ�, �÷��̾ ������ ���������� �ٲ��ֱ�.
//2. ��ư ������ �ٽ� ����â����.


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
		//Ÿ���� �ٸ� �̻��ϰ��� �浹�� ���ھ� �ø��� ����.
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

		//������ �浹. 

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
	//�̻��� �׷��ֱ�
	
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

	//�̻��� ��

	//�÷��̾� �׷��ֱ�

	this->Pturret.draw(outerhdc);

	//�÷��̾� �׷��ֱ� ��

	//ü�¹� �׷��ֱ�

	for (auto& i: shields)
	{
		i.draw(outerhdc, i.getcurVec().x, i.getcurVec().y);
	}
	//�÷��̾� ü�¹� ��

	//���̵� �׷��ֱ�

	Gdi_Draw_name(outerhdc, this->Pturret.getname());


	//����, ���̵� �׸��� ���ֱ�.

	Gdi_Draw_score(outerhdc, this->Pturret.getscore());

	//���� draw�ϰ� ���ֱ�.

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

