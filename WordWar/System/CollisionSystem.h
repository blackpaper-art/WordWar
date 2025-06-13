#pragma once
class Player;
class IBulletSystem;
class IEnemySystem;

class CollisionSystem
{
public:
	void HandleCollision(Player* p, IBulletSystem* bs, IEnemySystem* es);
};