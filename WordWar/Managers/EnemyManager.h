#pragma once
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Player.h"
#include "FieldManager.h"
#include "TimerManager.h"
#include "MainManager.h"
#include "../Interface/IEnemySystem.h"

#include <vector>
#include <memory>

class EnemyManager : public IEnemySystem
{
public:
	EnemyManager(TimerManager* tm, Player* p, FieldManager* fm);
	~EnemyManager();

	void SpawnEnemies(int x, int y, Player* p) override;
	void Update(float deltaTime);

	const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const override;

	void AddEliminatedEnemyCount(int count) override;
	const int GetEliminatedEnemyCount() const override;
private:
	std::vector<std::unique_ptr<Enemy>> enemies;

	Player* player;
	FieldManager* fieldManager;
	TimerManager* timerManager;

	int spawnInterval;
	int spawnTimerId;
	int eliminatedEnemyCount;
};
