#pragma once
#include "Character.h"
#include "../Managers/BulletManager.h"
#include "../Managers/TimerManager.h"

class Player;
class BulletManager;
class TimerManager;

class Player : public CharacterBase
{
public:
	Player(int x, int y, BulletManager* bm, TimerManager* tm);
	~Player();

	void Update(char input);
	int ShowPlayerInfo();
	void FireBullets(int bLevel, int rate);
	int GetPlayerLevel();
	void LevelUp();

private:
	BulletManager* bulletManager;
	TimerManager* timerManager;
	EnemyManager* enemyManager;

	int bulletLevel;
	int level;
	int bulletDir;
};