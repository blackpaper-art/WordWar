#include "HealthPackManager.h"
#include "../Managers/ConfigManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

HealthPackManager::HealthPackManager(TimerManager* tm)
    : timerManager(tm)
{
    // Spawn Health Pack with timer
    spawnTimer = timerManager->SetTimer(ConfigManager::GetInstance().GetHealthPackSpawnInterval(), [this] {
        SpawnHealthPack();
        }, true);
}

HealthPackManager::~HealthPackManager()
{
}

void HealthPackManager::SpawnHealthPack()
{
    int x = rand() % FIELD_WIDTH;
    int y = rand() % FIELD_HEIGHT;
    healthPacks.push_back(std::make_unique<HealthPack>(x, y));
}

void HealthPackManager::ClearDeadPacks()
{
    healthPacks.erase(
        std::remove_if(healthPacks.begin(), healthPacks.end(),
            [](const std::unique_ptr<HealthPack>& hp) {
                return hp->GetIsDead();
            }),
        healthPacks.end()
    );
}

const std::vector<std::unique_ptr<HealthPack>>& HealthPackManager::GetAllHealthPacks() const
{
    return healthPacks;
}