#include "Player.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Player::Player(int x, int y, BulletManager* bm, TimerManager* tm)
	:
	CharacterBase(x, y, 100, 1, 'P', false, 1), 
	bulletManager(bm), 
	timerManager(tm),
	bulletLevel(1)
{
	timerManager->SetTimer(1000, [=] { FireBullets(3,1); },  true);
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
}

int Player::ShowPlayerInfo()
{
	return GetHP();
}

void Player::FireBullets(int bLevel, int rate)
{
	if (bulletManager)
	{
		//According bullet level to fire bullet
		//level 1: One dir (UP)
		//level 2: Two dir (UP & DOWN)
		//level 3: Four dir (UP & DOWN & LEFT & RIGHT)
		switch (bLevel)
		{
		case 1: bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Up); break;
		case 2: 
			bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Up);
			bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Down); break;
		case 3:
			bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Up);
			bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Down); 
			bulletManager->SpawnBullet(GetX(), GetY() , MoveDir::Left);
			bulletManager->SpawnBullet(GetX(), GetY(), MoveDir::Right); break;
		default: break;
		}
		
	}
}

