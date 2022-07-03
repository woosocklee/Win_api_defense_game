#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Missile.h"
#include <vector>
#include "Resource.h"
#include "framework.h"
#include "Timer.h"

class Game_manager
{
private:
	void Changestage();

private:
	std::vector<Missile> missiles;
	Enemy enemys;

	RECT windowSize;
	Timer timer;
	double accumulatedTime = 0;
	double spawnrate = 1;


public:
	void addPmissile(Missile Pm);
	Player Pturret;
	Game_manager(RECT r);
	~Game_manager();
	void setwindowSize(RECT window);
	void Gdi_Draw_name(HDC hdc, std::wstring name);
	void Gdi_Draw_score(HDC hdc, int score);
	void Gdi_Draw_full_hpbar(HDC hdc, int x, int y);
	void Gdi_Draw_empty_hpbar(HDC hdc, int x, int y);
	void drawDoubleBuffring(/*HWND hWnd,*/ HDC hdc, HBITMAP hBackImage, BITMAP hBitback);
	
	HBITMAP hDoubleBufferImage;
	HBITMAP hBackImage;

	enum class Stage
	{
		Beginning,
		Gameplay,
		Ranking
	};
	Stage curStage;


public:
	void Update();
	void Draw(HDC hdc);
};


