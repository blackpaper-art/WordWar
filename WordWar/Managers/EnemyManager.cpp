#include "EnemyManager.h"
#include <set>

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

EnemyManager::EnemyManager(TimerManager* tm, Player* p, FieldManager* fm)
	:
	timerManager(tm),
	player(p),
	fieldManager(fm),
	eliminatedEnemyCount(0)
{
	timerManager->SetTimer(1000, [this] { 
		int randomX = rand() % FIELD_WIDTH;
		int randomY = rand() % FIELD_HEIGHT;
		if (player)
		{
			this->SpawnEnemies(randomX, randomY, player);
		}
	}, true);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::SpawnEnemies(int x, int y, Player* p)
{
	enemies.push_back(std::make_unique<Enemy>(x, y, p));
}

void EnemyManager::Update()
{
	//Save all alive enemies current position in occupiedPos
	std::set<std::pair<int, int>> occupiedPos;
	for (const auto& enemy : enemies)
	{
		if (enemy && !enemy->GetIsDead())
		{
			occupiedPos.insert({ enemy->GetX(), enemy->GetY() });
		}
	}

    auto it = enemies.begin();
    while (it != enemies.end())
    {
		if (!(*it) || (*it)->GetIsDead())
		{
			it = enemies.erase(it);
			continue;
		}

		//Preidc next position
		int nextX, nextY;
		(*it)->PredicNextPos(nextX, nextY);

		if (occupiedPos.count({ nextX,nextY }) == 0)
		{
			occupiedPos.erase({ (*it)->GetX(), (*it)->GetY() });
			occupiedPos.insert({ nextX,nextY });
			(*it)->SetX(nextX);
			(*it)->SetY(nextY);
		}
		++it;
    }
}

void EnemyManager::DrawAllEnemy()
{
	for (const auto& e : enemies) {
		int x = e->GetX();
		int y = e->GetY();
		if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
			if (fieldManager)
			{
				fieldManager->SetField(x, y, e->GetSymbol());
			}
		}
	}
}

const std::vector<std::unique_ptr<Enemy>>& EnemyManager::GetAllEnemy() const
{
	return enemies;
}

const int EnemyManager::GetEliminatedEnemyCount() const
{
	return eliminatedEnemyCount;
}

void EnemyManager::AddEliminatedEnemyCount(int count)
{
	eliminatedEnemyCount += count;
}
