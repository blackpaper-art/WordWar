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
	EnemyManager(TimerManager* tm);
	~EnemyManager();

	void InitPlayerPtr(Player* p);
	void SpawnEnemies(int x, int y, Player* p);
	void Update();
	void DrawAllEnemy();
	const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const;
private:
	std::vector<std::unique_ptr<Enemy>> enemies;

	Player* player;
	FieldManager fieldManager;
	TimerManager* timerManager;

	int spawnInterval;
	int spawnTimerId;
};
