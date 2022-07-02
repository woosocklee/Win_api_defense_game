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

Game_manager::Game_manager(const RECT r) : windowSize(r)
{

	if (!missiles.empty())
	{
		missiles = {};
	}
	this->curStage = Stage::Beginning;

}

Game_manager::~Game_manager()
{
}

void Game_manager::setwindowSize(RECT window)
{
	this->windowSize = window;
}

void Game_manager::Update()
{
	
	this->Changestage();
	for (auto& i : this->missiles)
	{
		//Ÿ���� �ٸ� �̻��ϰ��� �浹�� ���ھ� �ø��� ����.
		for (auto& j : this->missiles)
		{
			if (i.getmissileType() != j.getmissileType())
			{
				if (i.overlap(j))
				{
					this->Pturret.setscore(this->Pturret.getscore() + 100);
					i.setstate(false);
					j.setstate(false);
				}
			}
		}

		//������ �浹. 

		switch ((i.overlapwall(this->windowSize.right, this->windowSize.bottom)))
		{
		case 1:
			i.setstate(false);
			if (i.getmissileType())
			{
				this->Pturret.setHP(this->Pturret.getHP() - 1);
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
	this->enemys.update();




	const auto newEnd = std::remove_if(this->missiles.begin(), this->missiles.end(),
		[](const Missile& m) {return !m.getstate(); }
	);

	this->missiles.erase(newEnd, this->missiles.end());

}

void Game_manager::Draw(HDC hdc)
{
	//�̻��� �׷��ֱ�
	
	for (auto& i : this->missiles)
	{
		i.draw(hdc);
	}

	//�̻��� ��

	//�÷��̾� �׷��ֱ�

	this->Pturret.draw(hdc);

	//�÷��̾� �׷��ֱ� ��

	//ü�¹� �׷��ֱ�

	for (int i = 0; i < 10; i++)
	{
		if (i < this->Pturret.getHP())
		{
			Gdi_Draw_full_hpbar(hdc, 128*i, 1200); // rect���� bottom�� �޾ƿ��� �ϱ�.
		}
		else
		{
			Gdi_Draw_empty_hpbar(hdc, 128 * i, 1200);
		}
	}
	//�÷��̾� ü�¹� ��

	//���̵� �׷��ֱ�

	Gdi_Draw_name(hdc, this->Pturret.getname());


	//����, ���̵� �׸��� ���ֱ�.

	Gdi_Draw_score(hdc, this->Pturret.getscore());

	//���� draw�ϰ� ���ֱ�.
}

void Gdi_Draw_name(HDC hdc, std::wstring name)
{

	Graphics graphics(hdc);
	// >> txt
	SolidBrush brush(Color(255, 255, 0, 0));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF pointF(10.0f, 20.0f);
	graphics.DrawString(name.c_str(), -1, &font, pointF, &brush);
}

void Gdi_Draw_score(HDC hdc, int score)
{

	Graphics graphics(hdc);
	// >> txt
	SolidBrush brush(Color(255, 255, 0, 0));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF pointF(1000.0f, 20.0f);
	graphics.DrawString(std::to_wstring(score).c_str(), -1, &font, pointF, &brush);
}


void Gdi_Draw_full_hpbar(HDC hdc, int x, int y)
{
	Graphics graphics(hdc);
	Image img((WCHAR*)L"images/fullhp.png");
	int w = img.GetWidth();
	int h = img.GetHeight();
	graphics.DrawImage(&img, x - (w / 2), y - (h / 2), w, h);
}

void Gdi_Draw_empty_hpbar(HDC hdc, int x, int y)
{
	Graphics graphics(hdc);
	Image img((WCHAR*)L"images/emptyhp.png");
	int w = img.GetWidth();
	int h = img.GetHeight();
	graphics.DrawImage(&img, x - (w / 2), y - (h / 2), w, h);
}