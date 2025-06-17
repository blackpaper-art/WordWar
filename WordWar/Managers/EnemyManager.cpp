#include "EnemyManager.h"
#include "../Managers/ConfigManager.h"
#include <set>

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

EnemyManager::EnemyManager(IPlayerSystem* ps, FieldManager* fm)
    : playerSystem(ps), fieldManager(fm) {
}

EnemyManager::~EnemyManager() {}

void EnemyManager::Update(float deltaTime)
{
    int baseMs = ConfigManager::GetInstance().GetEnemyBaseSpawnInterval();
    int lvl = std::max(playerSystem->GetPlayerLevel(), 1);
    float spawnInterval = static_cast<float>(baseMs) / lvl;

    elapsedTime += deltaTime;

    if (elapsedTime >= spawnInterval) {
        elapsedTime = 0.0f;
        int x = rand() % ConfigManager::GetInstance().GetFieldWidth();
        int y = rand() % ConfigManager::GetInstance().GetFieldHeight();
        SpawnEnemies(x, y, playerSystem);
    }

    std::set<std::pair<int, int>> occupiedPos;
    for (const auto& enemy : enemies)
    {
        if (enemy && !enemy->GetIsDead()) {
            occupiedPos.insert({ enemy->GetX(), enemy->GetY() });
        }
    }

    auto it = enemies.begin();
    while (it != enemies.end())
    {
        if (!(*it) || (*it)->GetIsDead()) {
            it = enemies.erase(it);
            continue;
        }

        if ((*it)->CanMove(deltaTime))
        {
            int nextX, nextY;
            (*it)->PredicNextPos(nextX, nextY);
            if (occupiedPos.count({ nextX, nextY }) == 0)
            {
                occupiedPos.erase({ (*it)->GetX(), (*it)->GetY() });
                occupiedPos.insert({ nextX, nextY });
                (*it)->SetX(nextX);
                (*it)->SetY(nextY);
            }
        }
        ++it;
    }
}

void EnemyManager::SpawnEnemies(int x, int y, IPlayerSystem* ps)
{
    enemies.push_back(std::make_unique<Enemy>(x, y, ps));
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
