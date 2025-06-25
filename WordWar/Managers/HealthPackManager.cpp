#include "HealthPackManager.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize health pack spawn timer
// コンストラクタ：回復アイテムのスポーンタイマーを初期化
HealthPackManager::HealthPackManager(TimerManager* tm)
    : timerManager(tm)
{
    // Spawn health pack repeatedly using timer
    // タイマーで定期的に回復アイテムを生成
    spawnTimer = timerManager->SetTimer(
        ConfigManager::GetInstance().GetHealthPackSpawnInterval(),
        [this] { SpawnHealthPack(); },
        true
    );
}

// Destructor
// デストラクタ
HealthPackManager::~HealthPackManager() {}

// Spawn a new health pack at random position
// ランダムな位置に新しい回復アイテムを生成
void HealthPackManager::SpawnHealthPack()
{
    int x = rand() % ConfigManager::GetInstance().GetFieldWidth();
    int y = rand() % ConfigManager::GetInstance().GetFieldHeight();
    healthPacks.push_back(std::make_unique<HealthPack>(x, y));
}

// Remove dead health packs
// 使用済みの回復アイテムを削除
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

// Get all active health packs
// 現在の回復アイテムを取得
const std::vector<std::unique_ptr<HealthPack>>& HealthPackManager::GetAllHealthPacks() const
{
    return healthPacks;
}
