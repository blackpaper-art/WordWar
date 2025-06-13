#pragma once
#include "../Characters/Enemies/Enemy.h"

#include <vector>
#include <memory>

class IEnemySystem
{
public:
	virtual void SpawnEnemies(int x, int y, IPlayerSystem* p) = 0;
	virtual const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const = 0;

	virtual void AddEliminatedEnemyCount(int count) = 0;
	virtual const int GetEliminatedEnemyCount() const = 0;

	virtual ~IEnemySystem() {};
};