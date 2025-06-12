#pragma once


#include "Character.h"

#include "../Managers/TimerManager.h"

class Player;
class IBulletSystem;
class TimerManager;

class Player : public CharacterBase
{
public:
	Player(int x, int y, IBulletSystem* bs, TimerManager* tm);
	~Player();

	void Update(char input);
	int ShowPlayerInfo();
	void FireBullets(int bLevel, int rate);
	int GetPlayerLevel();
	void LevelUp();

private:
	IBulletSystem* bulletSystem;
	TimerManager* timerManager;

	int bulletLevel;
	int level;
	int bulletDir;
};