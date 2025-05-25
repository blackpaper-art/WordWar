#include "EnemyManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

EnemyManager::EnemyManager(TimerManager* tm)
	:
	timerManager(tm)
{
	timerManager->SetTimer(2000, [=] { 
		int randomX = rand() % FIELD_WIDTH;
		int randomY = rand() % FIELD_HEIGHT;
		this->SpawnEnemies(randomX, randomY, player);
	}, true);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::InitPlayerPtr(Player* p)
{
	player = p;
}

void EnemyManager::SpawnEnemies(int x, int y, Player* p)
{
	enemies.push_back(new Enemy(x, y, p));
}

void EnemyManager::Update()
{
	for (Enemy* e : enemies)
	{
		if(e) e->Update();
	}
}

void EnemyManager::DrawAllEnemy()
{
	for (Enemy* e : enemies) {
		int x = e->GetX();
		int y = e->GetY();
		if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
			fieldManager.SetField(x, y, e->GetSymbol());
		}
	}
}

const std::vector<Enemy*>& EnemyManager::GetAllEnemy() const
{
	return enemies;
}
