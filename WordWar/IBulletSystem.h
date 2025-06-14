#pragma once

#include "Items/Bullet.h";

#include <vector>
#include <memory>

class IBulletSystem
{
public:
	virtual void SpawnBullet(int x, int y, MoveDir dir) = 0;
	virtual const std::vector<std::unique_ptr<Bullet>>& GetAllBullets() const = 0;
	virtual int GetBulletCount() const = 0;
	virtual void StartSpawn() const = 0;
	virtual ~IBulletSystem() {}
};