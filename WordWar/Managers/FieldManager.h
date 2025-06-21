#pragma once
#include "TimerManager.h"

#include <stdio.h>
#include <memory>
#include <vector>

#define X_WALL 'X'      // Wall character X side / 横壁文字
#define Y_WALL 'Y'      // Wall character Y side / 縦壁文字
#define FIELD_NULL ' '  // Empty space character / 空白文字

class EnemyManager;
class TimerManager;
class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class IHealthPackSystem;

// Manager for the entire game field
// ゲームフィールド全体を管理するマネージャークラス
class FieldManager : public std::enable_shared_from_this<FieldManager>
{
public:
    std::shared_ptr<TimerHandle> countDownTimer; // Countdown timer / カウントダウンタイマー

    FieldManager();   // Constructor / コンストラクタ
    ~FieldManager();  // Destructor / デストラクタ

    const int GetFieldWidth() { return fieldWidth; }   // Get field width / フィールド幅取得
    const int GetFieldHeight() { return fieldHeight; } // Get field height / フィールド高さ取得

    void InitializeManagers(
        IPlayerSystem* ps,
        IEnemySystem* es,
        IBulletSystem* bs,
        IHealthPackSystem* hps,
        TimerManager* tm); // Initialize subsystems / 各サブシステム初期化

    void Update(float deltaTime);   // Update state / 状態更新
    void DrawField();               // Render field / フィールド描画
    void ShowDebugInfo(char input); // Toggle debug info by input / 入力でデバッグ表示切替

private:
    IEnemySystem* enemySystem;         // Enemy system reference / 敵システム参照
    IPlayerSystem* playerSystem;       // Player system reference / プレイヤーシステム参照
    IBulletSystem* bulletSystem;       // Bullet system reference / 弾システム参照
    IHealthPackSystem* healthPackSystem; // Health pack system reference / 回復アイテムシステム参照

    int fieldWidth;   // Field width / フィールド幅
    int fieldHeight;  // Field height / フィールド高さ
    std::vector<std::vector<char>> fieldBuffer; // Render buffer / 描画バッファ

    void CountDownTimer(); // Countdown timer logic / カウントダウン処理
    int countDownTime;     // Remaining time / 残り時間
    float myDeltaTime;     // Delta time for debug / デバッグ用デルタタイム

    bool showDebugMessage; // Debug info toggle flag / デバッグ表示フラグ
};
