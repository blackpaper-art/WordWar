#pragma once
#include "Character.h"
#include "Managers/BulletManager.h"

class Player;
class BulletManager;

class Player : public CharacterBase
{
public:
	Player(int x, int y, BulletManager* bm);
	~Player();

	void Update(char input);
	int ShowPlayerInfo();

private:
	BulletManager* bulletManager;
};