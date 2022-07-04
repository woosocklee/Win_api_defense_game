#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Missile.h"
#include "Shield.h"
#include <vector>
#include "Resource.h"
#include "framework.h"
#include "Timer.h"

class Game_manager
{

public:

	enum class Stage
	{
		Beginning,
		Gameplay,
		Ranking
	};
private:
	void Changestage();

	Stage curStage;

private:
	std::vector<Missile> missiles;
	Enemy enemys;
	std::vector<Shield> shields;

	Timer timer;
	double accumulatedTime = 0;
	double spawnrate = 3;


public:
	RECT windowSize;
	RECT oldWindowSize;
	void addPmissile(Missile Pm);
	Player Pturret;
	Game_manager(RECT r);
	~Game_manager();
	void setwindowSize(RECT window);
	void Gdi_Draw_name(HDC hdc, std::wstring name);
	void Gdi_Draw_score(HDC hdc, int score);
	void drawDoubleBuffring(/*HWND hWnd,*/ HDC hdc, HBITMAP hBackImage, BITMAP hBitback);
	
	HBITMAP hDoubleBufferImage;
	HBITMAP hBackImage;

	Stage getCurStage() const;


public:
	void Update();
	void Draw(HDC hdc);
};


