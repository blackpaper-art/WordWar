#include "Enemy.h"
#include "../../Managers/ConfigManager.h"

// Constructor: initialize enemy position and movement interval
// コンストラクタ���海領志辰頒��嚔g侯を兜豚晒
Enemy::Enemy(int x, int y, IPlayerSystem* ps)
    : CharacterBase(
        x, y, 
        ConfigManager::GetInstance().GetEnemyInitialHP(), 
        ConfigManager::GetInstance().GetEnemyInitialAP(),
        ConfigManager::GetInstance().GetEnemySymbol()[0],
        false, 1),
    playerSystem(ps),
    moveInterval(ConfigManager::GetInstance().GetEnemyMoveInterval()),
    timeAccumulator(0.0f)
{
}

// Destructor
// デストラクタ
Enemy::~Enemy() {}

// Check if enough time has passed to move
// 匯協�r�g�U�^瘁に卞�喊苗椶�登協
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
// プレイヤ�`に�鬚�って1ステップ卞�嗜箸鰉��y
void Enemy::PredicNextPos(int& outX, int& outY) const
{
    outX = GetX();
    outY = GetY();

    if (playerSystem->GetX() > outX) outX++;
    else if (playerSystem->GetX() < outX) outX--;

    if (playerSystem->GetY() > outY) outY++;
    else if (playerSystem->GetY() < outY) outY--;
}
