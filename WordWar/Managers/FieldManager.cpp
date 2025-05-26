#include "../Characters/Player.h"
#include "FieldManager.h"
#include "TimerManager.h"
#include "EnemyManager.h"
#include "BulletManager.h"

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
	for (const auto& b : bulletManager->GetAllBullet()) {
		if (!b || b->GetIsDead()) continue;

		for (Enemy* e : enemyManager->GetAllEnemy()) {
			if (!e || e->GetIsDead()) continue;

			if (b->GetX() == e->GetX() && b->GetY() == e->GetY()) {
				b->SetIsDead(true);
				e->SetIsDead(true);
			}
		}
	}
}

void FieldManager::DrawField()
{
	//Clean previous field
	system("cls");

	//Draw Field Top Wall
	for (int x = 0; x < FIELD_WIDTH + 2; x++)
	{
		putchar(X_WALL);
	}
	printf("\n");

	//Draw both Side Walls and main field
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		putchar(Y_WALL);
		//Draw main field like player enemy etc.
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			char ch = FIELD_NULL;

			if (y == player->GetY() && x == player->GetX())
				ch = player->GetSymbol();

			for (Enemy* e : enemyManager->GetAllEnemy()) {
				if (e && y == e->GetY() && x == e->GetX()) {
					if (!e->GetIsDead())
					{
						ch = e->GetSymbol();
						break;
					}
				}
			}

			for (const std::unique_ptr<Bullet>& b : bulletManager->GetAllBullet()) {
				if (b && y == b->GetY() && x == b->GetX()) {
					if (!b->GetIsDead())
					{
						ch = b->GetSymbol();
						break;
					}
				}
			}

			putchar(ch);
		}
		putchar(Y_WALL);
		printf("\n");
	}

	//Draw Field Down Walls
	for (int x = 0; x < FIELD_WIDTH + 2; x++)
	{
		putchar(X_WALL);
	}
	printf("\n");

	//ShowInfo
	printf("Bullets Count: %d", bulletManager->GetAllBullet().size());
}
