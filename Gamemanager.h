#pragma once
#include "Enemy.h"
#include "Player.h"
#include "missile.h"
#include <vector>

class Game_manager
{
private:
	void Changestage();

private:
	std::vector<missile> missiles;
	std::vector<Enemy> enemys;
	static Player Pturret;
	


public:
	enum class Stage
	{
		Beginning,
		Gameplay,
		Ranking
	};
public:
	void Update();
	void Draw();

};

