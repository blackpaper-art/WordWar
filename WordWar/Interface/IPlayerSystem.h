#pragma once
#include "../Characters/Player.h"

#include <vector>
#include <memory>

// Interface for player system
// プレイヤーシステム用インターフェース
class IPlayerSystem
{
public:
    // Get functions
    // プレイヤー情報取得系
    virtual int GetX() const = 0;         // Get X coordinate / X座標取得
    virtual int GetY() const = 0;         // Get Y coordinate / Y座標取得
    virtual int GetHP() const = 0;         // Get HP / HP取得
    virtual char GetSymbol() const = 0;   // Get symbol character / 表示文字取得
    virtual int GetPlayerLevel() = 0;     // Get player level / プレイヤーレベル取得
    virtual int GetEXPRemain() = 0;       // Get remaining EXP to next level / 次レベルまでのEXP取得

    // Get debug info
    // デバッグ用情報取得
    virtual int GetPlayerBulletLevel() = 0; // Get bullet level / 弾レベル取得

    // Changeable functions
    // プレイヤー状態変更系
    virtual void Initialize() = 0;           // Initialize player / 初期化
    virtual void UnderAttack(int damage) = 0; // Take damage / ダメージを受ける
    void FireBullets(int bLevel, int rate);  // Fire bullets / 弾を発射
    virtual void AddKillCount(int count) = 0; // Add kill count / 撃破数加算
    virtual void TryLevelUp() = 0;            // Try to level up / レベルアップ判定
    virtual void AddHP() = 0;                  // Restore HP / HP回復

    virtual ~IPlayerSystem() {};
};
