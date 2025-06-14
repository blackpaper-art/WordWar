/*---------------------------------------------------------------------------------------------*
 * Description / 説明 :                                                                         *
 *  FieldManager is responsible for managing the game field, including rendering,              *
 *  updating the field state, and delegating collision detection between bullets,              *
 *  enemies, and the player to the CollisionSystem.                                            *
 *                                                                                             *
 *  FieldManager クラスはゲームフィールドの管理を担当します。描画処理、状態の更新、                      *
 *  そして弾丸・敵・プレイヤー間の衝突判定を CollisionSystem に委託します。                            *
 *---------------------------------------------------------------------------------------------*/

#include "FieldManager.h"
#include "TimerManager.h"
#include "../Items/HealthPack.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IBulletSystem.h"
#include "../Interface/IPlayerSystem.h"
#include "../System/CollisionSystem.h"

#include <windows.h>
#include <algorithm>
#include <vector>
#include <memory>

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

FieldManager::FieldManager()
	:
	countDownTime(180)
{
	if (countDownTimer) {
		countDownTimer->isActive = false;
	}
}

FieldManager::~FieldManager()
{
}

void FieldManager::InitializeManagers(IPlayerSystem* ps, IEnemySystem* es, IBulletSystem* bs, HealthPack* hp, TimerManager* tm)
{
	playerSystem = ps;
	enemySystem = es;
	bulletSystem = bs;
	healthPack = hp;

	auto self = shared_from_this();
	countDownTimer = tm->SetTimer(1000, [weakSelf = std::weak_ptr<FieldManager>(self)] {
		if (auto s = weakSelf.lock()) {
			s->CountDownTimer();
		}
		}, true);
}

void FieldManager::Update(float deltaTime)
{
	//Update deltaTime
	myDeltaTime = deltaTime;
}

void FieldManager::DrawField()
{

	//1. Make a buffer and filled with null(" ") first
	char fieldBuffer[fieldHeight][fieldWidth];
	for (int y = 0; y < fieldHeight; y++)
	{
		for (int x = 0; x < fieldWidth; x++)
		{
			fieldBuffer[y][x] = FIELD_NULL;
		}
	}

	//2.1 Add Enemy data to the buffer
	if (enemySystem)
	{
		for (const auto& e : enemySystem->GetAllEnemy())
		{
			if (e && !e->GetIsDead())
			{
				fieldBuffer[e->GetY()][e->GetX()] = e->GetSymbol();
			}
		}
	}

	//2.2 Add Bullet data to the buffer
	if (bulletSystem)
	{
		for (const auto& b : bulletSystem->GetAllBullets())
		{
			if (b && !b->GetIsDead())
			{
				fieldBuffer[b->GetY()][b->GetX()] = b->GetSymbol();
			}
		}
	}

	//2.3 Add Player data to the buffer
	if (playerSystem)
	{
		fieldBuffer[playerSystem->GetY()][playerSystem->GetX()] = playerSystem->GetSymbol();
	}
	
	//2.4 Add Health Pack data to the buffer
	if (healthPack && !healthPack->GetIsDead())
	{
		fieldBuffer[healthPack->GetY()][healthPack->GetX()] = healthPack->GetSymbol();
	}
	
	//3. clean screen and display data
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	SetConsoleCursorPosition(hConsole, coordScreen);

	//3.1 Draw top wall
	for (int x = 0; x < FIELD_WIDTH + 2; x++)
	{
		putchar(X_WALL);
	}
	printf("\n");

	//3.2 Draw both Side Walls and Draw main field by the buffer
	for (int y = 0; y < fieldHeight; y++)
	{
		//Left Wall
		putchar(Y_WALL);

		//Main field
		for (int x = 0; x < fieldWidth; x++)
		{
			char c = fieldBuffer[y][x];
			if (c == healthPack->GetSymbol()) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				putchar(c);
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (c == playerSystem->GetSymbol())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				putchar(c);
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else {
				putchar(c);
			}
			
		}

		//Right Wall
		putchar(Y_WALL);

		//Right Info board
		if (y == 0)
		{
			printf(" Time Left: %-4d seconds", countDownTime);
		}
		else if (y == 1)
		{
			printf(" Player HP: %-4d", playerSystem->GetHP());
		}
		else if (y == 2){
			printf(" Player Level: %d", playerSystem->GetPlayerLevel());
		}
		else if (y == 3) {
			printf(" Next Level: %-4d enemies left", playerSystem->GetEXPRemain());
		}
		else if (y == 5) {
			printf(" ---DEBUG INFO---");
		}
		else if (y == 6) {
			printf(" DeltaTime: %f", myDeltaTime);
		}
		else if (y == 7) {
			printf(" Player Bullet Interval: %-4d ms", 1000 / playerSystem->GetPlayerBulletLevel());
		}
		printf("\n");

		
	}

	//3.3 Draw down wall
	for (int x = 0; x < FIELD_WIDTH + 2; x++)
	{
		putchar(X_WALL);
	}
	printf("\n");
	
	//4. ShowInfo
	int liveEnemyCount = 0;
	if (enemySystem)
	{
		const auto& enemies = enemySystem->GetAllEnemy();
		liveEnemyCount = static_cast<int>(std::count_if(
			enemies.begin(), 
			enemies.end(), 
			[](const std::unique_ptr<Enemy>& e) {
			return e && !e->GetIsDead();
		}
			));
	}
	
	printf(" Eliminated enemy Count: %d", enemySystem->GetEliminatedEnemyCount());
}

void FieldManager::CountDownTimer()
{
	countDownTime--;
	// Time's up — force the player to die and end the game
	if (countDownTime <= 0 && playerSystem)
	{
		playerSystem->UnderAttack(playerSystem->GetHP());
	}
}
