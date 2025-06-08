#include "GameMain.h"
#include "Characters/Player.h"
#include "Managers/BulletManager.h"
#include "Managers/EnemyManager.h"
#include "Managers/TimerManager.h"
#include "Managers/FieldManager.h"

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <memory>

//Create main smart pointers
std::unique_ptr <Player> player;
std::unique_ptr <TimerManager> timerManager;
std::unique_ptr <FieldManager> fieldManager;
std::unique_ptr <EnemyManager> enemyManager;
std::unique_ptr <BulletManager> bulletManager;

int main() {
	//Initialize
	InitializeMainGame();

	//MainLoop
	MainGameLoop();

	//Shutdown
	ShutdownGame();
	return 0;
}

void InitializeMainGame()
{
	//Create Manager objects
	fieldManager = std::make_unique<FieldManager>();
	bulletManager = std::make_unique<BulletManager>();

	//Initialize internal pointers for each manager
	player = std::make_unique<Player>(fieldManager->GetFieldWidth() / 2, fieldManager->GetFieldHeight() / 2, bulletManager.get(), timerManager.get());

	enemyManager = std::make_unique<EnemyManager>(timerManager.get(), player.get(), fieldManager.get());

	if (fieldManager)
	{
		fieldManager->InitializeManagers(player.get(), timerManager.get(), enemyManager.get(), bulletManager.get());
	}
	if (bulletManager)
	{
		bulletManager->InitFieldPtr(fieldManager.get());
	}
}

void MainGameLoop() {
	clock_t lastTime = clock();
	while (true)
	{
		//Manual Update (when player inputed)
		if (_kbhit()) {
			char playerInput = _getch();
			player->Update(playerInput);
			fieldManager->DrawField();
		}

		//Auto update (by using clock)
		clock_t currentTime = clock();
		float deltaTime = currentTime - lastTime / CLOCKS_PER_SEC;
		if (currentTime >= lastTime + TIME_GAP)
		{
			bulletManager->Update();
			enemyManager->Update();
			fieldManager->Update();

			fieldManager->DrawField();
			lastTime = currentTime;
		}
		
	}
}

void ShutdownGame()
{
}