#include "EnemyManager.h"
#include "../Managers/ConfigManager.h"
#include <set>

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

// Constructor
// ���󥹥ȥ饯��
EnemyManager::EnemyManager(IPlayerSystem* ps, FieldManager* fm)
    : playerSystem(ps), fieldManager(fm) {
}

// Destructor
// �ǥ��ȥ饯��
EnemyManager::~EnemyManager() {}

// Update enemy spawning and movement
// �������ɤ��ƄӤ���¤���
void EnemyManager::Update(float deltaTime)
{
    // Calculate spawn interval based on player level
    // �ץ쥤��`��٥�ˏꤸ�ƥ��ݩ`���g����Ӌ��
    int baseMs = ConfigManager::GetInstance().GetEnemyBaseSpawnInterval();
    int lvl = std::max(playerSystem->GetPlayerLevel(), 1);
    float spawnInterval = static_cast<float>(baseMs) / lvl;

    elapsedTime += deltaTime;

    // Spawn new enemy if interval passed
    // �g���򳬤������¤�����������
    if (elapsedTime >= spawnInterval) {
        elapsedTime = 0.0f;
        int width = ConfigManager::GetInstance().GetFieldWidth();
        int height = ConfigManager::GetInstance().GetFieldHeight();

        int x = 0, y = 0;
        int side = rand() % 4;  // 0: top, 1: bottom, 2: left, 3: right

        switch (side) {
        case 0: // top
            y = 0;
            x = rand() % width;
            break;
        case 1: // bottom
            y = height - 1;
            x = rand() % width;
            break;
        case 2: // left
            x = 0;
            y = rand() % height;
            break;
        case 3: // right
            x = width - 1;
            y = rand() % height;
            break;
        }
        SpawnEnemies(x, y, playerSystem);
    }

    // Track occupied positions
    // ռ�����ˤ�ӛ�h
    std::set<std::pair<int, int>> occupiedPos;
    for (const auto& enemy : enemies)
    {
        if (enemy && !enemy->GetIsDead()) {
            occupiedPos.insert({ enemy->GetX(), enemy->GetY() });
        }
    }

    // Update each enemy
    // �����������
    auto it = enemies.begin();
    while (it != enemies.end())
    {
        // Remove dead enemies
        // �������������
        if (!(*it) || (*it)->GetIsDead()) {
            it = enemies.erase(it);
            continue;
        }

        // Move enemy if ready
        // �Ƅӿ��ܤʤ��Ƅ�
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

// Spawn new enemy
// �¤�����������
void EnemyManager::SpawnEnemies(int x, int y, IPlayerSystem* ps)
{
    enemies.push_back(std::make_unique<Enemy>(x, y, ps));
}

// Get all enemies
// ȫ�ƤΔ���ȡ��
const std::vector<std::unique_ptr<Enemy>>& EnemyManager::GetAllEnemy() const
{
    return enemies;
}

// Get total eliminated enemy count
// ���Ɯg�ߤΔ�����ȡ��
const int EnemyManager::GetEliminatedEnemyCount() const
{
    return eliminatedEnemyCount;
}

// Add to eliminated enemy count
// �����������
void EnemyManager::AddEliminatedEnemyCount(int count)
{
    eliminatedEnemyCount += count;
}
