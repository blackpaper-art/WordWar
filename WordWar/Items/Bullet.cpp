#include "Bullet.h"

Bullet::Bullet(int x, int y, MoveDir dir)
	:CharacterBase(x, y, 1, 1, '.', false), direction(dir)
{}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!this->GetIsDead())
	{
		int newX = GetX(), newY = GetY();

		//Check Dir
		switch (direction)
		{
		case MoveDir::Up:
			newY--;
			break;
		case MoveDir::Down:
			newY++;
			break;
		case MoveDir::Left:
			newX--;
			break;
		case MoveDir::Right:
			newX++;
			break;
		default:
			break;
		}

		//Set to new position
		SetY(newY);
		SetX(newX);

		if (newY < 0)
		{
			SetIsDead(true);
		}
	}
	else {
		return;
	}
}

