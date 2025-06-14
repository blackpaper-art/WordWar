#pragma once
#include "../Characters/Enemies/Enemy.h"
#include "FieldManager.h"
#include "TimerManager.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"

#include <vector>
#include <memory>

class EnemyManager : public IEnemySystem, public std::enable_shared_from_this<EnemyManager>
{
public:
	EnemyManager(TimerManager* tm, IPlayerSystem* p, FieldManager* fm);
	~EnemyManager();

	void StartSpawn();
	void SpawnEnemies(int x, int y, IPlayerSystem* p) override;
	void Update(float deltaTime);

	const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const override;

	void AddEliminatedEnemyCount(int count) override;
	const int GetEliminatedEnemyCount() const override;
private:
	std::shared_ptr<TimerHandle> spawnTimer;
	std::vector<std::unique_ptr<Enemy>> enemies;

	IPlayerSystem* playerSystem;
	FieldManager* fieldManager;
	TimerManager* timerManager;

	int spawnInterval;
	int spawnTimerId;
	int eliminatedEnemyCount;
};
