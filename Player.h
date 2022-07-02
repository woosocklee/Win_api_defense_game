#pragma once
#include "Vector2D.h"
#include "missile.h"
#include <string>
class Player
{
private:
	std::string Name;
	int HP;
	Vector2D missileSpawnPoint;
	Vector2D MissileDirection;
	Vector2D TurretCurpos;
	
public:
	Player();
	~Player();
	Missile* shotmissile();
	void setHP(int newhp);
	
	void update();
	//좌클릭시 미사일 발사
	//마우스 포인터를 따라가면서 발사할 수 있게 하기
	//a랑 d로 양 옆으로 움직일 수 있게 하기. 속도 주기.
	//점수 따면 기록하기
	//체력 모두 잃으면 사망하고, 점수 조건에 따라 기록할지 말지 결정하게 점수 올려주기.
	//플레이어의 다이렉션의 y값이 +가 되지 않게 하기.
};