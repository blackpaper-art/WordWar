#include "GameMain.h"
#include "Characters/Player.h"
#include "Managers/BulletManager.h"
#include "Managers/EnemyManager.h"
#include "Managers/TimerManager.h"
#include "Managers/FieldManager.h"

#include <stdio.h>
#include <conio.h>
#include <time.h>

Player* player;
TimerManager* timerManager = new TimerManager;
EnemyManager* enemyManager = new EnemyManager(timerManager);
FieldManager* fieldManager = new FieldManager;
BulletManager* bulletManager = new BulletManager();

void MainGameLoop() {
	clock_t lastTime = clock();
	while (true)
	{
		clock_t currentTime = clock();
		//Auto update (by using clock)
		if (currentTime >= lastTime + TIME_GAP)
		{
			lastTime = currentTime;

			bulletManager->Update();
			bulletManager->DrawAllBullets();
			enemyManager->Update();
			enemyManager->DrawAllEnemy();
			fieldManager->Update();
			fieldManager->DrawField();
		}
		//Manual Update (when player inputed)
		if (_kbhit()) {
			char playerInput = _getch();
			player->Update(playerInput);
			fieldManager->DrawField();
		}
	}
}

int main() {
	//Initialize
	player = new Player(fieldManager->GetFieldWidth() / 2, fieldManager->GetFieldHeight() / 2, bulletManager, timerManager);

	if (fieldManager)
	{
		fieldManager->InitializeManagers(player, timerManager, enemyManager, bulletManager);
	}
	if (bulletManager)
	{
		bulletManager->InitFieldPtr(fieldManager);
	}
	if (enemyManager)
	{
		enemyManager->InitPlayerPtr(player);
		enemyManager->SpawnEnemies(1, 1, player);
	}

	//MainLoop
	MainGameLoop();
	delete player;
	return 0;
}