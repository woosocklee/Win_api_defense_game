#pragma once
#include "Vector2D.h"
#include <string>
class Player
{
private:
	std::string Name;
	int HP;
	Vector2D missileSpawnPoint;
	Vector2D MissileDirection;
	Vector2D TurretCurpos;

	//좌클릭시 미사일 발사
	//마우스 포인터를 따라가면서 발사할 수 있게 하기
	//a랑 d로 양 옆으로 움직일 수 있게 하기. 속도 주기.
	//점수 따면 기록하기
	//체력 모두 잃으면 사망하고, 점수 조건에 따라 기록할지 말지 결정하게 점수 올려주기.
};