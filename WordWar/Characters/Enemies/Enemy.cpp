#include "Enemy.h"

Enemy::Enemy(int x, int y, IPlayerSystem* ps)
	:
	CharacterBase(x, y, 1, 1, 'i', false, 1), playerSystem(ps),
	moveInterval(1000.0f),
	timeAccumulator(0.0f)
{
}

Enemy::~Enemy()
{
}

// Check can move
// 移動可能判定
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

// Move one step toward player
// プレイヤー方向へ一歩
void Enemy::PredicNextPos(int& outX, int& outY) const
{
	outX = GetX();
	outY = GetY();
	
	if (playerSystem->GetX() > outX) outX++;
	else if (playerSystem->GetX() < outX) outX--;

	if (playerSystem->GetY() > outY) outY++;
	else if (playerSystem->GetY() < outY) outY--;
}