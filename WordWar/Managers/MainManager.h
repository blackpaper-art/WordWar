/*---------------------------------------------------------------------------------------------*
 * Describe:                                                                                   *
 *  MainManager is responsible for centrally managing gameplay-related data and state by       *
 *  retrieving information from other managers (such as EnemyManager, BulletManager, etc.).    *
 *  It acts as a mediator to reduce direct dependencies and cross-referencing between          *
 *  individual managers, promoting a decoupled and modular game architecture.                  *
 *---------------------------------------------------------------------------------------------*/

#pragma once
#include "BulletManager.h"
#include "EnemyManager.h"
#include "FieldManager.h"
#include "TimerManager.h"

class MainManager
{
public:
	MainManager(Player* p, BulletManager* bm, EnemyManager* em, FieldManager* fm, TimerManager* tm);
	~MainManager();

	const Player* GetPlayer() const;
	const BulletManager* GetBulletManager() const;
	const EnemyManager* GetEnemyManager() const;
	const FieldManager* GetFieldManager() const;
	const TimerManager* GetTimerManager() const;

private:
	int playerLevel;
	int eliminatedEnemyCount;

	Player* player;
	BulletManager* bulletManager;
	EnemyManager* enemyManager;
	FieldManager* fieldManager;
	TimerManager* timerManager;
};
