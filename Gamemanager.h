#pragma once

class Game_manager
{
private:
	void Changestage();



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

