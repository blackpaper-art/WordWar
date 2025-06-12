#include "MainManager.h"

MainManager::MainManager(Player* p, BulletManager* bm, EnemyManager* em, FieldManager* fm, TimerManager* tm)
	:
	player(p),
	bulletManager(bm),
	enemyManager(em),
	fieldManager(fm),
	timerManager(tm),

	playerLevel(0),
	eliminatedEnemyCount(0)
{
	if (player)
	{
		playerLevel = player->GetPlayerLevel();
	}
	if (enemyManager)
	{
		eliminatedEnemyCount = enemyManager->GetEliminatedEnemyCount();
	}
}

MainManager::~MainManager()
{
}

const Player* MainManager::GetPlayer() const
{
	return player;
}

const BulletManager* MainManager::GetBulletManager() const
{
	return bulletManager;
}

const EnemyManager* MainManager::GetEnemyManager() const
{
	return enemyManager;
}

const FieldManager* MainManager::GetFieldManager() const
{
	return fieldManager;
}

const TimerManager* MainManager::GetTimerManager() const
{
	return timerManager;
}