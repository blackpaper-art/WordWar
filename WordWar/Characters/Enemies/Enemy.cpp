#include "Enemy.h"

// Constructor: initialize enemy position and movement interval
// コンストラクタ：敵の位置と移動間隔を初期化
Enemy::Enemy(int x, int y, IPlayerSystem* ps)
    : CharacterBase(x, y, 1, 1, 'i', false, 1),
    playerSystem(ps),
    moveInterval(1000.0f),
    timeAccumulator(0.0f)
{
}

// Destructor
// デストラクタ
Enemy::~Enemy() {}

// Check if enough time has passed to move
// 一定時間経過後に移動可能か判定
bool Enemy::CanMove(float deltaTime)
{
    timeAccumulator += deltaTime;
    if (timeAccumulator >= moveInterval)
    {
        timeAccumulator = 0.0f;
        return true;
    }
    return false;
}

// Predict next position by stepping one step closer to player
// プレイヤーに向かって1ステップ移動先を予測
void Enemy::PredicNextPos(int& outX, int& outY) const
{
    outX = GetX();
    outY = GetY();

    if (playerSystem->GetX() > outX) outX++;
    else if (playerSystem->GetX() < outX) outX--;

    if (playerSystem->GetY() > outY) outY++;
    else if (playerSystem->GetY() < outY) outY--;
}
