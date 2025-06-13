#pragma once
class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class HealthPack;

class CollisionSystem
{
public:
	void HandleCollision(IPlayerSystem* ps, IBulletSystem* bs, IEnemySystem* es, HealthPack* hp);
};