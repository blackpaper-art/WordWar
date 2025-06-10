#pragma once
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Player.h"
#include "FieldManager.h"
#include "TimerManager.h"
#include <vector>
#include <memory>

class EnemyManager
{
public:
	EnemyManager(TimerManager* tm, Player* p, FieldManager* fm);
	~EnemyManager();

	void SpawnEnemies(int x, int y, Player* p);
	void Update();
	void DrawAllEnemy();
	const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const;

	void AddEliminatedEnemyCount(int count);
	const int GetEliminatedEnemyCount() const;
private:
	std::vector<std::unique_ptr<Enemy>> enemies;

	Player* player;
	FieldManager* fieldManager;
	TimerManager* timerManager;

	int spawnInterval;
	int spawnTimerId;
	int eliminatedEnemyCount;
};
