#include "Player.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Player::Player(int x, int y, BulletManager* bm, TimerManager* tm)
	:
	CharacterBase(x, y, 100, 1, 'P', false), 
	bulletManager(bm), 
	timerManager(tm)
{
	timerManager->SetTimer(2000, [=] { bulletManager->SpawnBullet(GetX(), GetY() - 1, MoveDir::Up); },  true);
}

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

	//Fire

}

int Player::ShowPlayerInfo()
{
	return GetHP();
}

void Player::FireBullets(int bulletCount, int rate)
{
	if (bulletManager)
	{
		bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Up);
	}
}

