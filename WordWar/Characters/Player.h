#pragma once
#include "Character.h"
#include "../Interface/IPlayerSystem.h"
#include "../Managers/TimerManager.h"

class IBulletSystem;
class TimerManager;

// Player class: handles player control, shooting, and level system
// プレイヤークラス：操作、弾発射、レベルシステムを管理
class Player : public CharacterBase, public IPlayerSystem, public std::enable_shared_from_this<Player>
{
public:
    std::shared_ptr<TimerHandle> fireTimer; // Timer for firing bullets / 弾発射用タイマー

    Player(int x, int y, IBulletSystem* bs, TimerManager* tm); // Constructor / コンストラクタ
    ~Player(); // Destructor / デストラクタ

    // Process input and update player state
    // 入力を処理しプレイヤー状態を更新
    void Update(char input);

    // IPlayerSystem overrides
    // IPlayerSystemインターフェース実装
    void Initialize() override;           // Initialize player / プレイヤー初期化
    int GetX() const override;            // Get X coordinate / X座標取得
    int GetY() const;                     // Get Y coordinate / Y座標取得
    int GetHP() const override;           // Get HP / HP取得
    char GetSymbol() const override;      // Get symbol / 表示文字取得
    int GetPlayerLevel() override;        // Get level / レベル取得
    int GetPlayerBulletLevel() override;  // Get bullet level / 弾レベル取得
    int GetEXPRemain() override;          // Get EXP remaining / 次レベルまでのEXP取得

    void AddKillCount(int count) override; // Add kill count / 撃破数加算
    void TryLevelUp() override;            // Try to level up / レベルアップ判定
    void FireBullets(int bLevel, int rate); // Fire bullets / 弾発射
    void UnderAttack(int damage) override;  // Take damage / ダメージ処理
    void AddHP() override;                  // Restore HP / HP回復

    void Shutdown(); // Stop timers and cleanup / タイマー停止と後片付け

private:
    IBulletSystem* bulletSystem; // Bullet system reference / 弾システム参照
    TimerManager* timerManager;  // Timer manager reference / タイマーマネージャー参照

    int fireTimerID;             // Fire timer ID (unused) / 弾発射タイマーID（未使用）

    int bulletLevel;             // Bullet level / 弾レベル
    int bulletDir;               // Bullet direction / 弾方向

    // EXP & Level system
    // EXP・レベルシステム
    int level;                   // Player level / プレイヤーレベル
    int killCount;               // Total kill count / 撃破数
    int nextLevelKills;          // Kills required for next level / 次レベル必要撃破数
};
