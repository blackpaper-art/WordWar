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

// Create main smart pointers
// ��Ҫ�ʥ��ީ`�ȥݥ��󥿤�����
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
		// Show start screen
		// �����`�Ȼ�����ʾ
		ShowStartScreen();

		// Initialize game
		// ���`����ڻ�
		InitializeMainGame();

		// Main game loop
		// �ᥤ�󥲩`���`��
		MainGameLoop();

		// Shutdown and cleanup
		// ����åȥ��������Ƭ����
		ShutdownGame();
	}
	return 0;
}

// Display start screen
// �����`�Ȼ����ʾ
void ShowStartScreen()
{
	// Clear console screen
	// ���楯�ꥢ
	system("cls");

	printf("\n\n\n\n\n");
	printf("=========================================================\n");
	printf("                    W O R D   W A R\n");
	printf("=========================================================\n\n");
	printf("  Controls / ��������:\n");
	printf("    [W][A][S][D] : Move / �Ƅ�\n");
	printf("    Kill enemies to level up! / ���򵹤��ƥ�٥륢�åף�\n");
	printf("    Collect [+] to recover HP / [+]��HP�؏�\n\n");
	printf("=========================================================\n");
	printf("  Press [ENTER] to Start / [ENTER]���`���_ʼ\n");
	printf("=========================================================\n");
	printf("\n  Thanks / ���x:\n");
	printf("    - nlohmann/json (https://github.com/nlohmann/json)\n");
	printf("=========================================================\n");

	// Wait until [ENTER] pressed
	// [ENTER]��Ѻ�����ޤǴ��C
	while (getchar() != '\n') {}
}

// Initialize game systems and managers
// ���`��θ������ƥ�ȥޥͩ`����`����ڻ�
void InitializeMainGame()
{
	system("cls");

	ConfigManager::GetInstance().LoadConfig("Settings/config.json");

	timerManager = std::make_unique<TimerManager>();
	fieldManager = std::make_shared<FieldManager>();
	bulletManager = std::make_unique<BulletManager>();

	player = std::make_shared<Player>(
		ConfigManager::GetInstance().GetFieldWidth() / 2,
		ConfigManager::GetInstance().GetFieldHeight() / 2,
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

// Main game loop
// �ᥤ�󥲩`���`��
void MainGameLoop() {
	clock_t lastTime = clock();
	int lastLevel = player->GetPlayerLevel();

	while (!player->GetIsDead())
	{
		// Manual update (when player inputs)
		// �ץ쥤��`�����r���քӸ���
		if (_kbhit()) {
			char playerInput = _getch();
			player->Update(playerInput);
			fieldManager->ShowDebugInfo(playerInput);
			fieldManager->DrawField();
		}

		// Auto update (using clock)
		// �ԄӸ��£��r�g�U�^�ˤ�룩
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

// Clean up resources after game ends
// ���`��K����Υ꥽�`�����
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

// Display game over screen
// ���`�४�`�Щ`������ʾ
void ShowGameOverScreen(int totalKills, int maxLevel)
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("=========================================================\n");
	printf("                G A M E   O V E R\n");
	printf("=========================================================\n\n");
	printf("  You have been defeated... / ���`�४�`�Щ`...\n\n");
	printf("	Total Kills / �t������:  %d\n", totalKills);
	printf("	Max Level / ��ߥ�٥�:  %d\n\n", maxLevel);
	printf("	Thanks for playing! / �ץ쥤���꤬�Ȥ���\n\n");
	printf("=========================================================\n");
	system("pause"); 

	// Wait until [ENTER] pressed
	// [ENTER]��Ѻ�����ޤǴ��C
	while (getchar() != '\n') {} 
}
