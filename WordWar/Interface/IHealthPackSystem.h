#pragma once

#include <vector>
#include <memory>

class HealthPack;

// Interface for health pack system
// 回復アイテムシステム用インターフェース
class IHealthPackSystem
{
public:
    // Get all active health packs
    // 現在の回復アイテムを取得
    virtual const std::vector<std::unique_ptr<HealthPack>>& GetAllHealthPacks() const = 0;

    // Spawn a new health pack
    // 新しい回復アイテムを生成
    virtual void SpawnHealthPack() = 0;

    // Remove dead or used health packs
    // 使い切った回復アイテムを削除
    virtual void ClearDeadPacks() = 0;

    virtual ~IHealthPackSystem() {};
};
