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
	timerManager->SetTimer(2000, [this] { 
		int randomX, randomY;
		int edge = rand() % 4; // 0: top, 1: bottom, 2: left, 3: right

		switch (edge) {
		case 0: // top
			randomY = 0;
			randomX = rand() % FIELD_WIDTH;
			break;
		case 1: // bottom
			randomY = FIELD_HEIGHT - 1;
			randomX = rand() % FIELD_WIDTH;
			break;
		case 2: // left
			randomX = 0;
			randomY = rand() % FIELD_HEIGHT;
			break;
		case 3: // right
			randomX = FIELD_WIDTH - 1;
			randomY = rand() % FIELD_HEIGHT;
			break;
		}

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

void EnemyManager::Update(float deltaTime)
{
	//Save the current positions of all alive enemies in occupiedPos
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
		//Remove dead enemies
		if (!(*it) || (*it)->GetIsDead())
		{
			it = enemies.erase(it);
			continue;
		}

		//Check if the enemy is ready to move (based on deltaTime)
		if ((*it)->CanMove(deltaTime))
		{
			//Predict the next position
			int nextX, nextY;
			(*it)->PredicNextPos(nextX, nextY);

			//Move if the next position is not occupied
			if (occupiedPos.count({ nextX,nextY }) == 0)
			{
				occupiedPos.erase({ (*it)->GetX(), (*it)->GetY() });
				occupiedPos.insert({ nextX,nextY });
				(*it)->SetX(nextX);
				(*it)->SetY(nextY);
			}
		}
		//Move to the next enemy regardless of whether this one moved
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
