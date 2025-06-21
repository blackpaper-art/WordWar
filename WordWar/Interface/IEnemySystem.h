#pragma once
#include "../Characters/Enemies/Enemy.h"

#include <vector>
#include <memory>

// Interface for enemy system
// 敵システム用インターフェース
class IEnemySystem
{
public:
    // Spawn new enemies at specified position
    // 指定位置に敵を生成
    virtual void SpawnEnemies(int x, int y, IPlayerSystem* p) = 0;

    // Get all active enemies
    // 現在の全ての敵を取得
    virtual const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const = 0;

    // Add to eliminated enemy count
    // 撃破数を加算
    virtual void AddEliminatedEnemyCount(int count) = 0;

    // Get total eliminated enemy count
    // 撃破済みの敵数を取得
    virtual const int GetEliminatedEnemyCount() const = 0;

    virtual ~IEnemySystem() {};
};
