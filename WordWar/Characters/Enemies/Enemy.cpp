#include "Enemy.h"

Enemy::Enemy(int x, int y, Player* p)
	:
	CharacterBase(x, y, 1, 1, 'E', false, 1), player(p),
	moveInterval(1000.0f),
	timeAccumulator(0.0f)
{
}

Enemy::~Enemy()
{
}


bool Enemy::CanMove(float deltaTime)
{
	timeAccumulator += deltaTime;
	if (timeAccumulator >= moveInterval)
	{
		timeAccumulator = 0.0f;
		return true;
	}
	return false;
}

void Enemy::PredicNextPos(int& outX, int& outY) const
{
	outX = GetX();
	outY = GetY();
	
	if (player->GetX() > outX) outX++;
	else if (player->GetX() < outX) outX--;

	if (player->GetY() > outY) outY++;
	else if (player->GetY() < outY) outY--;
}