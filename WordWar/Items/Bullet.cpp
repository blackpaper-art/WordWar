#include "Bullet.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Bullet::Bullet(int x, int y, MoveDir dir)
	:
	CharacterBase(x, y, 1, 1, '.', false, 1),
	direction(dir),
	isOutOfField(false)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!this->GetIsDead())
	{
		int newX = GetX(), newY = GetY();
		//int postX = GetX() + 1, postY = GetX() + 1;

		//Check Dir
		switch (direction)
		{
		case MoveDir::Up:    newY -= 1; break;
		case MoveDir::Down:  newY += 1; break;
		case MoveDir::Left:  newX -= 1; break;
		case MoveDir::Right: newX += 1; break;
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

