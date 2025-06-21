#pragma once

#include "../Items/Bullet.h"

#include <vector>
#include <memory>

// Interface for bullet system
// 弾システム用インターフェース
class IBulletSystem
{
public:
    // Spawn a bullet with specified direction and level
    // 指定した方向とレベルで弾を生成
    virtual void SpawnBullet(int x, int y, MoveDir dir, int bulletLevel) = 0;

    // Get all active bullets
    // 現在の全ての弾を取得
    virtual const std::vector<std::unique_ptr<Bullet>>& GetAllBullets() const = 0;

    // Get current bullet count
    // 弾の総数を取得
    virtual int GetBulletCount() const = 0;

    virtual ~IBulletSystem() {}
};
