#pragma once

#include "../Character.h"
#include "../../Characters/Player.h"

class Enemy :public CharacterBase
{
public:
	Enemy(int x, int y, Player* p);
	~Enemy();

	bool CanMove(float deltaTime);
	void PredicNextPos(int& outX, int& outY) const;
private:
	Player* player;
	int preX, preY;

	float moveInterval;
	float timeAccumulator;
};