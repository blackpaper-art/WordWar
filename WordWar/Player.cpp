#include "Player.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Player::Player(int x, int y) 
	:
	CharacterBase(x, y, 100, 1, 'P') 
{}

Player::~Player()
{
}

void Player::Update(char input)
{
	//Movement
	int newX = GetX(), newY = GetY();

	switch (input)
	{
	case 'w': newY--; break;
	case 's': newY++; break;
	case 'a': newX--; break;
	case 'd': newX++; break;
	default: break;
	}

	if (newX >= 0 && newX < FIELD_WIDTH &&
		newY >= 0 && newY < FIELD_HEIGHT)
	{
		SetX(newX);
		SetY(newY);
	}
}

int Player::ShowPlayerInfo()
{
	return GetHP();
}
