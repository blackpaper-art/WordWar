/*---------------------------------------------------------------------------------------------*
 * Describe:                                                                                   *
 *  FieldManager is responsible for managing the main game field, including rendering,         *
 *  updating the field state, and handling collision detection between bullets, enemies,       *
 *  and the player.                                                                            *
 *---------------------------------------------------------------------------------------------*/

#include "../Characters/Player.h"
#include "FieldManager.h"
#include "TimerManager.h"
#include "EnemyManager.h"
#include "BulletManager.h"

#include <windows.h>
#include <algorithm>
#include <vector>
#include <memory>

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

FieldManager::FieldManager()
{
}

FieldManager::~FieldManager()
{
}

char FieldManager::GetField(int x, int y)
{
	return field[y][x];
}

void FieldManager::SetField(int x, int y, char intern)
{
	field[y][x] = intern;
}

void FieldManager::InitializeManagers(Player* p, TimerManager* tm, EnemyManager* em, BulletManager* bm)
{
	player = p;
	timerManager = tm;
	enemyManager = em;
	bulletManager = bm;
}

void FieldManager::Update()
{
	//Check collision
	for (const auto& b : bulletManager->GetAllBullet()) {
		if (!b || b->GetIsDead()) continue;

		for (const auto& e : enemyManager->GetAllEnemy()) {
			if (!e || e->GetIsDead()) continue;

			if (b->GetX() == e->GetX() && b->GetY() == e->GetY()) {
				e->UnderAttack(b->GetAttackPower());
				b->UnderAttack(e->GetAttackPower());

				enemyManager->AddEliminatedEnemyCount(1);
				break; //Prevent collison with multi enemies
			}
			else if (player && player->GetX() == e->GetX() && player->GetY() == e->GetY()){
				e->UnderAttack(b->GetAttackPower());
				enemyManager->AddEliminatedEnemyCount(1);

				player->UnderAttack(e->GetAttackPower());
				break;
			}
		}
	}
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
	if (enemyManager)
	{
		for (const auto& e : enemyManager->GetAllEnemy())
		{
			if (e && !e->GetIsDead())
			{
				fieldBuffer[e->GetY()][e->GetX()] = e->GetSymbol();
			}
		}
	}

	//2.2 Add Bullet data to the buffer
	if (bulletManager)
	{
		for (const auto& b : bulletManager->GetAllBullet())
		{
			if (b && !b->GetIsDead())
			{
				fieldBuffer[b->GetY()][b->GetX()] = b->GetSymbol();
			}
		}
	}

	//2.3 Add Player data to the buffer
	if (player)
	{
		fieldBuffer[player->GetY()][player->GetX()] = player->GetSymbol();
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
			putchar(fieldBuffer[y][x]);
		}

		//Right Wall
		putchar(Y_WALL);
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
	if (enemyManager)
	{
		const auto& enemies = enemyManager->GetAllEnemy();
		liveEnemyCount = static_cast<int>(std::count_if(
			enemies.begin(), 
			enemies.end(), 
			[](const std::unique_ptr<Enemy>& e) {
			return e && !e->GetIsDead();
		}
			));
	}
	printf("Player HP: %-4d", player->GetHP());
	printf(" Eliminated enemy Count: %d", enemyManager->GetEliminatedEnemyCount());
}
