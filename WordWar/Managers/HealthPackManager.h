#pragma once

#include "../Items/HealthPack.h"
#include "../Managers/TimerManager.h"
#include "../Interface/IHealthPackSystem.h"

#include <vector>
#include <memory>

// Manager for spawning and managing health packs
// 回復アイテムの生成と管理を行うマネージャークラス
class HealthPackManager : public IHealthPackSystem
{
public:
    HealthPackManager(TimerManager* tm); // Constructor / コンストラクタ
    ~HealthPackManager();                // Destructor / デストラクタ

    void SpawnHealthPack() override;     // Spawn a health pack / 回復アイテムを生成
    void ClearDeadPacks() override;      // Remove dead health packs / 使用済みアイテムを削除
    const std::vector<std::unique_ptr<HealthPack>>& GetAllHealthPacks() const override; // Get all packs / 全アイテム取得

    void Shutdown() {
        // Stop the spawn timer safely
        // スポーンタイマーを安全に停止
        if (spawnTimer) {
            spawnTimer->Stop();
            spawnTimer.reset();
        }
    }

private:
    std::vector<std::unique_ptr<HealthPack>> healthPacks; // Active health packs / 現在の回復アイテム
    std::shared_ptr<TimerHandle> spawnTimer;              // Timer handle for spawning / スポーンタイマー

    TimerManager* timerManager;                           // Timer manager reference / タイマーマネージャー
};
