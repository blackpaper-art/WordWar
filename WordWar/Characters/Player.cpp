#include "Player.h"
#include "../IBulletSystem.h"
#include "../Items/Bullet.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Player::Player(int x, int y, IBulletSystem* bs, TimerManager* tm)
	:
	CharacterBase(x, y, 100, 1, 'P', false, 1),
	bulletSystem(bs),
	timerManager(tm),
	bulletLevel(1),
	level(1),
	bulletDir(0)
{
	timerManager->SetTimer(1000 / bulletLevel, [=] { FireBullets(level, bulletLevel); },  true);
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
	case 'w': newY--; bulletDir = 0; break;
	case 's': newY++; bulletDir = 1; break;
	case 'a': newX--; bulletDir = 2; break;
	case 'd': newX++; bulletDir = 3; break;
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
	if (bulletSystem)
	{
		//According bullet level to fire bullet
		//level 1: One dir (UP)
		//level 2: Two dir (UP & DOWN)
		//level 3: Four dir (UP & DOWN & LEFT & RIGHT)
		//level 4: Eight dir (UP & DOWN & LEFT & RIGHT 
		//					& UP LEFT & UP DOWN & DOWN LEFT & DOWN RIGHT)
		std::vector<MoveDir> directions;

		switch (bulletDir)
		{
		case 0:directions = { MoveDir::Up }; break;
		case 1:directions = { MoveDir::Down }; break;
		case 2:directions = { MoveDir::Left }; break;
		case 3:directions = { MoveDir::Right }; break;
		default: break;
		}

		/*switch (bLevel)
		{
		case 1:
			directions = { MoveDir::Up };
			break;
		case 2:
			directions = { MoveDir::Up, MoveDir::Down };
			break;
		case 3:
			directions = { MoveDir::Up, MoveDir::Down, MoveDir::Left, MoveDir::Right };
			break;
		case 4:
			directions = {
				MoveDir::Up, MoveDir::Down, MoveDir::Left, MoveDir::Right,
				MoveDir::UpLeft, MoveDir::UpRight, MoveDir::DownLeft, MoveDir::DownRight
			};
			break;
		default: break;
		}*/

		for (const auto& dir : directions)
		{
			bulletSystem->SpawnBullet(GetX(), GetY(), dir);
		}
		
	}
}

int Player::GetPlayerLevel()
{
	return level;
}

void Player::LevelUp()
{
	level++;
}

