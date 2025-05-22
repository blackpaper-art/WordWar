#include "Bullet.h"

Bullet::Bullet(int x, int y)
	:CharacterBase(x, y, 1, 1, '.')
{}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	int newX = GetX(), newY = GetY();
	newY--;
	SetY(newY);
}
