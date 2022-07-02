#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Missile.h"
#include <vector>
#include "Resource.h"

class Game_manager
{
private:
	void Changestage();

private:
	std::vector<Missile> missiles;
	Enemy enemys;
	Player Pturret;
	RECT windowSize;

public:
	Game_manager(RECT r);
	~Game_manager();
	void setwindowSize(RECT window);
	enum class Stage
	{
		Beginning,
		Gameplay,
		Ranking
	};
	Stage curStage;
public:
	void Update();
	void Draw();

};

