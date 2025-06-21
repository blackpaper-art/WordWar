#pragma once

#include "../Character.h"
#include "../../Characters/Player.h"

// Enemy character class
// 敵キャラクタークラス
class Enemy : public CharacterBase
{
public:
    Enemy(int x, int y, IPlayerSystem* ps); // Constructor / コンストラクタ
    ~Enemy();                               // Destructor / デストラクタ

    // Check if enemy can move based on elapsed time
    // 経過時間に基づいて移動可能か判定
    bool CanMove(float deltaTime);

    // Predict next position towards player
    // プレイヤーに向かって次の位置を予測
    void PredicNextPos(int& outX, int& outY) const;

private:
    IPlayerSystem* playerSystem; // Reference to player system / プレイヤー情報参照
    float moveInterval;          // Movement interval (ms) / 移動間隔
    float timeAccumulator;       // Time accumulator for movement / 移動用時間累積
};
