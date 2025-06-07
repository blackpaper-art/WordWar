#include "Enemy.h"

Enemy::Enemy(int x, int y, Player* p)
	:
	CharacterBase(x, y, 1, 1, 'E', false), player(p)
{
}

Enemy::~Enemy()
{
}

void Enemy::SpawnEnemy(int x, int y)
{
}

void Enemy::Update() 
{
	ApproachToPlayer();
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

void Enemy::ApproachToPlayer()
{
	//Movement
	if (player)
	{
		int newX = GetX(), newY = GetY();

		if (player->GetX() > newX)
		{
			newX++;
		}
		else if (player->GetX() < newX)
		{
			newX--;
		}
		if (player->GetY() > newY)
		{
			newY++;
		}
		else if (player->GetY() < newY)
		{
			newY--;
		}
		
		preX = newX;
		preY = newY;

		SetX(newX);
		SetY(newY);
	}
}
