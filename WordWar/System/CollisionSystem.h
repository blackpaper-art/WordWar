#pragma once
class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;

class CollisionSystem
{
public:
	void HandleCollision(IPlayerSystem* ps, IBulletSystem* bs, IEnemySystem* es);
};