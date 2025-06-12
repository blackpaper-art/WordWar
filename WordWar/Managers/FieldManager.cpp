/*---------------------------------------------------------------------------------------------*
 * Describe:                                                                                   *
 *  FieldManager is responsible for managing the main game field, including rendering,         *
 *  updating the field state, and handling collision detection between bullets, enemies,       *
 *  and the player.                                                                            *
 *---------------------------------------------------------------------------------------------*/

#include "../Characters/Player.h"
#include "FieldManager.h"
#include "TimerManager.h"
#include "../Interface/IEnemySystem.h"
#include "../IBulletSystem.h"

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
	timerManager->SetTimer(1000, [=] {CountDownTimer(); }, true);
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

void FieldManager::InitializeManagers(Player* p, TimerManager* tm, IEnemySystem* es, IBulletSystem* bs)
{
	player = p;
	timerManager = tm;
	enemySystem = es;
	bulletSystem = bs;
}

void FieldManager::Update(float deltaTime)
{
	//Check collision
	for (const auto& b : bulletSystem->GetAllBullets()) {
		if (!b || b->GetIsDead()) continue;

		for (const auto& e : enemySystem->GetAllEnemy()) {
			if (!e || e->GetIsDead()) continue;

			if (b->GetX() == e->GetX() && b->GetY() == e->GetY()) {
				e->UnderAttack(b->GetAttackPower());
				b->UnderAttack(b->GetHP());

				enemySystem->AddEliminatedEnemyCount(1);
				Beep(1500, 10);
				break; //Prevent collison with multi enemies
			}
			else if (player && player->GetX() == e->GetX() && player->GetY() == e->GetY()){
				player->UnderAttack(e->GetAttackPower());
				e->UnderAttack(e->GetAttackPower());

				enemySystem->AddEliminatedEnemyCount(1);
				Beep(300, 10);
				break;
			}
		}
	}

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

		//Right Info board
		if (y == 0)
		{
			printf(" Time Left: %-4d seconds", countDownTime);
		}
		else if (y == 1)
		{
			printf(" Player HP: %-4d", player->GetHP());
		}
		else if (y == 2){
			printf(" Player Level: %d", player->GetPlayerLevel());
		}
		else if (y == 5) {
			printf(" DeltaTime: %f", myDeltaTime);
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
	// Time's up ¡ª force the player to die and end the game
	if (countDownTime <= 0 && player)
	{
		player->UnderAttack(player->GetHP());
	}
}
