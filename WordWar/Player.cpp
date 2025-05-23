#include "Player.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Player::Player(int x, int y, BulletManager* bm)
	:
	CharacterBase(x, y, 100, 1, 'P', false), bulletManager(bm)
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
	case ' ':
		if (bulletManager) {
			bulletManager->SpawnBullet(GetX(), GetY() - 1, MoveDir::Up);
		}
		break;
	default: break;
	}

	if (newX >= 0 && newX < FIELD_WIDTH &&
		newY >= 0 && newY < FIELD_HEIGHT)
	{
		SetX(newX);
		SetY(newY);
	}

	//Fire

}

int Player::ShowPlayerInfo()
{
	return GetHP();
}
