#pragma once
#include "../Character.h"
#include "../../Characters/Player.h"
#include "../../Managers/BulletManager.h"

class Enemy :public CharacterBase
{
public:
	Enemy(int x, int y, Player* p);
	~Enemy();

	void SpawnEnemy(int x, int y);
	void Update();
private:
	void ApproachToPlayer();
	Player* player;
};