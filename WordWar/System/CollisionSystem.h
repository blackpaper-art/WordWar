#pragma once
class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class IHealthPackSystem;

class CollisionSystem
{
public:
	void HandleCollision(IPlayerSystem* ps, IBulletSystem* bs, IEnemySystem* es, IHealthPackSystem* hp);
};