#include "Player.h"
#include "../Interface/IBulletSystem.h"
#include "../Items/Bullet.h"
#include "../Managers/ConfigManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

// Constructor: initialize player properties
// コンストラクタ：プレイヤーの初期値を設定
Player::Player(int x, int y, IBulletSystem* bs, TimerManager* tm)
    : CharacterBase(x, y,
        ConfigManager::GetInstance().GetPlayerInitialHP(),
        1,
        ConfigManager::GetInstance().GetPlayerSymbol()[0],
        false,
        ConfigManager::GetInstance().GetPlayerInitialAP()
    ),
    bulletSystem(bs),
    timerManager(tm),
    bulletLevel(1),
    level(1),
    killCount(0),
    nextLevelKills(10),
    bulletDir(0)
{
}

// Destructor: stop fire timer if active
// デストラクタ：発射タイマーがあれば停止
Player::~Player()
{
    if (fireTimer) {
        fireTimer->isActive = false;
    }
}

// Update player position based on input
// 入力に応じてプレイヤーの位置を更新
void Player::Update(char input)
{
    int newX = CharacterBase::GetX(), newY = CharacterBase::GetY();

    switch (input)
    {
    case 'w': newY--; bulletDir = 0; break; // Up
    case 's': newY++; bulletDir = 1; break; // Down
    case 'a': newX--; bulletDir = 2; break; // Left
    case 'd': newX++; bulletDir = 3; break; // Right
    default: break;
    }

    if (newX >= 0 && newX < FIELD_WIDTH &&
        newY >= 0 && newY < FIELD_HEIGHT)
    {
        SetX(newX);
        SetY(newY);
    }
}

// Add to kill count and check level up
// 撃破数を加算し、レベルアップ判定
void Player::AddKillCount(int count)
{
    killCount += count;
    TryLevelUp();
}

// Try to level up based on kill count
// 撃破数に応じてレベルアップを判定
void Player::TryLevelUp()
{
    int baseKills = 10;
    float growthFactor = 1.5f;

    while (killCount >= nextLevelKills)
    {
        killCount -= nextLevelKills;
        level++;
        nextLevelKills = baseKills * level * growthFactor;

        // Every 3 levels, increase bullet level
        // 3レベルごとに弾レベルをアップ
        if (level % 3 == 0) {
            bulletLevel++;
        }
    }
}

// Fire bullets in multiple directions based on level
// プレイヤーレベルに応じて多方向に弾を発射
void Player::FireBullets(int bLevel, int rate)
{
    if (bulletSystem)
    {
        std::vector<MoveDir> directions;

        switch (bulletDir)
        {
        case 0: // Up
            directions.push_back(MoveDir::Up);
            if (bLevel >= 2) directions.push_back(MoveDir::Down);
            if (bLevel >= 3) {
                directions.push_back(MoveDir::Left);
                directions.push_back(MoveDir::Right);
            }
            if (bLevel >= 4) {
                directions.push_back(MoveDir::UpLeft);
                directions.push_back(MoveDir::UpRight);
                directions.push_back(MoveDir::DownLeft);
                directions.push_back(MoveDir::DownRight);
            }
            break;
        case 1: // Down
            directions.push_back(MoveDir::Down);
            if (bLevel >= 2) directions.push_back(MoveDir::Up);
            if (bLevel >= 3) {
                directions.push_back(MoveDir::Left);
                directions.push_back(MoveDir::Right);
            }
            if (bLevel >= 4) {
                directions.push_back(MoveDir::UpLeft);
                directions.push_back(MoveDir::UpRight);
                directions.push_back(MoveDir::DownLeft);
                directions.push_back(MoveDir::DownRight);
            }
            break;
        case 2: // Left
            directions.push_back(MoveDir::Left);
            if (bLevel >= 2) directions.push_back(MoveDir::Right);
            if (bLevel >= 3) {
                directions.push_back(MoveDir::Up);
                directions.push_back(MoveDir::Down);
            }
            if (bLevel >= 4) {
                directions.push_back(MoveDir::UpLeft);
                directions.push_back(MoveDir::UpRight);
                directions.push_back(MoveDir::DownLeft);
                directions.push_back(MoveDir::DownRight);
            }
            break;
        case 3: // Right
            directions.push_back(MoveDir::Right);
            if (bLevel >= 2) directions.push_back(MoveDir::Left);
            if (bLevel >= 3) {
                directions.push_back(MoveDir::Up);
                directions.push_back(MoveDir::Down);
            }
            if (bLevel >= 4) {
                directions.push_back(MoveDir::UpLeft);
                directions.push_back(MoveDir::UpRight);
                directions.push_back(MoveDir::DownLeft);
                directions.push_back(MoveDir::DownRight);
            }
            break;
        default:
            directions.push_back(MoveDir::Up);
            break;
        }

        // Fire all directions
        // 全方向に弾を生成
        for (const auto& dir : directions)
        {
            bulletSystem->SpawnBullet(CharacterBase::GetX(), CharacterBase::GetY(), dir, bulletLevel);
        }
    }
}

// Interfaces implementation

// Get player level
// プレイヤーレベル取得
int Player::GetPlayerLevel() { return level; }

// Get bullet level
// 弾レベル取得
int Player::GetPlayerBulletLevel() { return bulletLevel; }

// Get remaining EXP to next level
// 次レベルまでのEXP取得
int Player::GetEXPRemain() { return nextLevelKills - killCount; }

// Get X coordinate
// X座標取得
int Player::GetX() const { return CharacterBase::GetX(); }

// Get Y coordinate
// Y座標取得
int Player::GetY() const { return CharacterBase::GetY(); }

// Get HP
// HP取得
int Player::GetHP() const { return CharacterBase::GetHP(); }

// Get symbol character
// 表示文字取得
char Player::GetSymbol() const { return CharacterBase::GetSymbol(); }

// Initialize player and start fire timer
// プレイヤー初期化と発射タイマー開始
void Player::Initialize() {
    auto self = shared_from_this();
    fireTimer = timerManager->SetTimer(
        ConfigManager::GetInstance().GetPlayerFireInterval() / GetPlayerLevel(),
        [weakSelf = std::weak_ptr<Player>(self)] {
            if (auto s = weakSelf.lock()) {
                s->FireBullets(s->GetPlayerLevel(), s->level);
            }
        }, true);
}

// Take damage
// ダメージ処理
void Player::UnderAttack(int damage) {
    CharacterBase::UnderAttack(damage);
}

// Restore HP
// HPを回復
void Player::AddHP() {
    CharacterBase::SetHP(10);
}

// Shutdown: stop fire timer safely
// シャットダウン：発射タイマーを安全に停止
void Player::Shutdown() {
    if (fireTimer) {
        fireTimer->Stop();
        fireTimer.reset();
    }
}
