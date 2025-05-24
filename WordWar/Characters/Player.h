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
	Player(int x, int y, BulletManager* bm);
	~Player();

	void Update(char input);
	int ShowPlayerInfo();
	void FireBullets(int bulletCount, int rate);
private:
	BulletManager* bulletManager;
	TimerManager* timerManager;
};