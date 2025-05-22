#pragma once
#include "Character.h"

class Player;

class Player : public CharacterBase
{
public:
	Player(int x, int y);
	~Player();

	void Update(char input);
	int ShowPlayerInfo();
private:

};