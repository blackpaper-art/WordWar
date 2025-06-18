#include "Bullet.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Bullet::Bullet(int x, int y, MoveDir dir, int bulletLevel)
	:
	CharacterBase(x, y, bulletLevel, 1, '.', false, 1),
	direction(dir),
	isOutOfField(false),
	moveInterval(100.0f),
	timeAccumulator(0.0f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	if (!this->GetIsDead() && CanMove(deltaTime))
	{
		int newX = GetX(), newY = GetY();
		//int postX = GetX() + 1, postY = GetX() + 1;

		//Check Dir
		switch (direction)
		{
		case MoveDir::Up:			newY -= 1; break;
		case MoveDir::Down:			newY += 1; break;
		case MoveDir::Left:			newX -= 1; break;
		case MoveDir::Right:		newX += 1; break;
		case MoveDir::UpLeft:		newY += 1; newX -= 2; break;
		case MoveDir::UpRight:		newY += 1; newX += 2; break;
		case MoveDir::DownLeft:		newY -= 1; newX -= 2; break;
		case MoveDir::DownRight:	newY -= 1; newX += 2; break;
		default: break;
		}

		if (newX < 0 || newX >= FIELD_WIDTH || newY < 0 || newY >= FIELD_HEIGHT)
		{
			isOutOfField = true;
			return;
		}
		//Set to new position
		SetY(newY);
		SetX(newX);
	}
}

bool Bullet::GetIsOutOfField()
{
	return isOutOfField;
}

bool Bullet::CanMove(float deltaTime)
{
	timeAccumulator += deltaTime;
	if (timeAccumulator >= moveInterval)
	{
		timeAccumulator = 0.0f;
		return true;
	}
	return false;
}