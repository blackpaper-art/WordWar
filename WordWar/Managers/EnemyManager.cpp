#include "EnemyManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

EnemyManager::EnemyManager(TimerManager* tm)
	:
	timerManager(tm)
{
	timerManager->SetTimer(2000, [this] { 
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
	enemies.push_back(std::make_unique<Enemy>(x, y, p));
}

void EnemyManager::Update()
{
    auto e = enemies.begin();
    while (e != enemies.end())
    {
		if (e->get() == nullptr)
		{
			e = enemies.erase(e);
			continue;
		}

		(*e)->Update();

		if ((*e)->GetIsDead())
		{
			e = enemies.erase(e);
		}
		else
		{
			++e;
		}
    }
}

void EnemyManager::DrawAllEnemy()
{
	for (const auto& e : enemies) {
		int x = e->GetX();
		int y = e->GetY();
		if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
			fieldManager.SetField(x, y, e->GetSymbol());
		}
	}
}

const std::vector<std::unique_ptr<Enemy>>& EnemyManager::GetAllEnemy() const
{
	return enemies;
}
