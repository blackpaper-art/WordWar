#include "GameMain.h"

#include "Characters/Player.h"

#include "Managers/BulletManager.h"
#include "Managers/EnemyManager.h"
#include "Managers/TimerManager.h"
#include "Managers/FieldManager.h"
#include "Managers/ConfigManager.h"
#include "Managers/HealthPackManager.h"  

#include "System/CollisionSystem.h"

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <memory>

//Create main smart pointers
std::shared_ptr <Player> player;
std::shared_ptr <FieldManager> fieldManager;
std::shared_ptr <EnemyManager> enemyManager;

std::unique_ptr <TimerManager> timerManager;
std::unique_ptr <BulletManager> bulletManager;
std::unique_ptr <CollisionSystem> collisionSystem;
std::unique_ptr <HealthPackManager> healthPackManager;

int main() {
	while (true)
	{
		//Start Screen
		ShowStartScreen();

		//Initialize
		InitializeMainGame();

		//MainLoop
		MainGameLoop();

		//Shutdown
		ShutdownGame();
	}
	return 0;
}

void ShowStartScreen()
{
	system("cls"); //Clean screen

	printf("\n\n\n\n\n");
	printf("=========================================================\n");
	printf("                    W O R D   W A R\n");
	printf("=========================================================\n\n");
	printf("  Controls / 操作方法:\n");
	printf("    [W][A][S][D] : Move / 移動\n");
	printf("    Kill enemies to level up! / 敵を倒してレベルアップ！\n");
	printf("    Collect [+] to recover HP / [+]でHP回復\n\n");
	printf("=========================================================\n");
	printf("  Press [ENTER] to Start / [ENTER]キーで開始\n");
	printf("=========================================================\n");
	printf("\n  Thanks / 感謝:\n");
	printf("    - nlohmann/json (https://github.com/nlohmann/json)\n");
	printf("=========================================================\n");

	while (getchar() != '\n') {} // Wait player press Enter key
}

void InitializeMainGame()
{
	system("cls");

	ConfigManager::GetInstance().LoadConfig("Settings/config.json");

	timerManager = std::make_unique<TimerManager>();
	fieldManager = std::make_shared<FieldManager>();
	bulletManager = std::make_unique<BulletManager>();

	player = std::make_shared<Player>(
		fieldManager->GetFieldWidth() / 2,
		fieldManager->GetFieldHeight() / 2,
		static_cast<IBulletSystem*>(bulletManager.get()),
		timerManager.get()
	);

	enemyManager = std::make_shared<EnemyManager>(
		static_cast<IPlayerSystem*>(player.get()),
		fieldManager.get()
	);

	collisionSystem = std::make_unique<CollisionSystem>();
	healthPackManager = std::make_unique<HealthPackManager>(timerManager.get());

	fieldManager->InitializeManagers(
		player.get(),
		enemyManager.get(),
		bulletManager.get(),
		healthPackManager.get(),
		timerManager.get()
	);

	player->Initialize();
}

void MainGameLoop() {
	clock_t lastTime = clock();
	int lastLevel = player->GetPlayerLevel();

	while (!player->GetIsDead())
	{
		//Manual Update (when player inputed)
		if (_kbhit()) {
			char playerInput = _getch();
			player->Update(playerInput);
			fieldManager->ShowDebugInfo(playerInput);
			fieldManager->DrawField();
		}

		//Auto update (by using clock)
		clock_t currentTime = clock();
		float deltaTime = currentTime - lastTime;
		if (currentTime >= lastTime + TIME_GAP)
		{
			bulletManager->Update(deltaTime);
			enemyManager->Update(deltaTime);
			fieldManager->Update(deltaTime);
			collisionSystem->HandleCollision(
				static_cast<IPlayerSystem*>(player.get()), 
				static_cast<IBulletSystem*>(bulletManager.get()), 
				static_cast<IEnemySystem*>(enemyManager.get()),
				static_cast<IHealthPackSystem*>(healthPackManager.get())
			);
			fieldManager->DrawField();
			lastTime = currentTime;
		}
	}
}

void ShutdownGame()
{
	ShowGameOverScreen(enemyManager.get()->GetEliminatedEnemyCount(), player.get()->GetPlayerLevel());

	if (player) player->Shutdown();
	if (healthPackManager) healthPackManager->Shutdown();

	timerManager.reset();
	bulletManager.reset();
	collisionSystem.reset();
	fieldManager.reset();
	player.reset();
	enemyManager.reset();
	healthPackManager.reset();
}

void ShowGameOverScreen(int totalKills, int maxLevel)
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("=========================================================\n");
	printf("                G A M E   O V E R\n");
	printf("=========================================================\n\n");
	printf("  You have been defeated... / ゲームオーバー...\n\n");
	printf("	Total Kills / 総撃破数:  %d\n", totalKills);
	printf("	Max Level / 最高レベル:  %d\n\n", maxLevel);
	printf("	Thanks for playing! / プレイありがとう！\n\n");
	printf("=========================================================\n");
	system("pause"); 
	while (getchar() != '\n') {} // Wait player press Enter key
}
