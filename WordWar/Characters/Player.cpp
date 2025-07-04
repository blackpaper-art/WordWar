#include "Player.h"
#include "../Interface/IBulletSystem.h"
#include "../Items/Bullet.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize player properties
// コンストラクタ�坤廛譽ぅ筴`の兜豚�､鰓O協
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
    bulletLevel(ConfigManager::GetInstance().GetPlayerInitialBulletLevel()),
    level(ConfigManager::GetInstance().GetPlayerInitialPlayerLevel()),
    killCount(0),
    nextLevelKills(ConfigManager::GetInstance().GetPlayerLevelUpBaseKills()),
    bulletDir(0)
{
}

// Destructor: stop fire timer if active
// デストラクタ�紺k符タイマ�`があれば唯峭
Player::~Player()
{
    if (fireTimer) {
        fireTimer->isActive = false;
    }
}

// Update player position based on input
// 秘薦に鬉犬謄廛譽ぅ筴`の了崔を厚仟
void Player::Update(char input)
{
    int newX = CharacterBase::GetX(), newY = CharacterBase::GetY();

    switch (input)
    {
    case 'w': case 'W':
        newY--;
        bulletDir = 0;
        break;

    case 's': case 'S':
        newY++;
        bulletDir = 1;
        break;

    case 'a': case 'A':
        newX--;
        bulletDir = 2;
        break;

    case 'd': case 'D':
        newX++;
        bulletDir = 3;
        break;

    }

    if (newX >= 0 && newX < ConfigManager::GetInstance().GetFieldWidth() &&
        newY >= 0 && newY < ConfigManager::GetInstance().GetFieldHeight())
    {
        SetX(newX);
        SetY(newY);
    }
}

// Add to kill count and check level up
// �墜栃�を紗麻し、レベルアップ登協
void Player::AddKillCount(int count)
{
    killCount += count;
    TryLevelUp();
}

// Try to level up based on kill count
// �墜栃�に鬉犬謄譽戰襯▲奪廚鯏亢�
void Player::TryLevelUp()
{
    int baseKills = 10;
    float growthFactor = ConfigManager::GetInstance().GetPlayerLevelUpGrowthFactor();

    while (killCount >= nextLevelKills)
    {
        killCount -= nextLevelKills;
        level++;
        nextLevelKills = baseKills * level * growthFactor;

        // Every ' GetPlayerBulletUpBaseLevel ' levels, increase bullet level
        // 仝GetPlayerBulletUpBaseLevel々のレベルごとに�･譽戰襪鬟▲奪�
        if (level % ConfigManager::GetInstance().GetPlayerBulletUpBaseLevel() == 0) {
            bulletLevel++;
        }

		// Update fire timer interval based on new level
		// 仟しいレベルに鬉犬動k符タイマ�`の�g侯を厚仟
        if (fireTimer) {
            fireTimer->Stop();
        }

        auto self = shared_from_this();
        fireTimer = timerManager->SetTimer(
            ConfigManager::GetInstance().GetPlayerInitialFireInterval() / GetPlayerLevel(),
            [weakSelf = std::weak_ptr<Player>(self)] {
                if (auto s = weakSelf.lock()) {
                    s->FireBullets(s->GetPlayerLevel());
                }
            }, true);
    }
}

// Fire bullets in multiple directions based on level
// プレイヤ�`レベルに鬉犬洞犒熟鬚��､魄k符
void Player::FireBullets(int bLevel)
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
        // 畠圭�鬚��､鯢�撹
        for (const auto& dir : directions)
        {
            bulletSystem->SpawnBullet(CharacterBase::GetX(), CharacterBase::GetY(), dir, bulletLevel);
        }
    }
}

// Interfaces implementation

// Get player level
// プレイヤ�`レベル函誼
int Player::GetPlayerLevel() { return level; }

// Get bullet level
// �･譽戰詒ゝ�
int Player::GetPlayerBulletLevel() { return bulletLevel; }

// Get remaining EXP to next level
// 肝レベルまでのEXP函誼
int Player::GetEXPRemain() { return nextLevelKills - killCount; }

// Get X coordinate
// X恙�鉾ゝ�
int Player::GetX() const { return CharacterBase::GetX(); }

// Get Y coordinate
// Y恙�鉾ゝ�
int Player::GetY() const { return CharacterBase::GetY(); }

// Get HP
// HP函誼
int Player::GetHP() const { return CharacterBase::GetHP(); }

// Get symbol character
// 燕幣猟忖函誼
char Player::GetSymbol() const { return CharacterBase::GetSymbol(); }

// Initialize player and start fire timer
// プレイヤ�`兜豚晒と�k符タイマ�`�_兵
void Player::Initialize() {
    auto self = shared_from_this();
    fireTimer = timerManager->SetTimer(
        ConfigManager::GetInstance().GetPlayerInitialFireInterval() / GetPlayerLevel(),
        [weakSelf = std::weak_ptr<Player>(self)] {
            if (auto s = weakSelf.lock()) {
                s->FireBullets(s->GetPlayerLevel());
            }
        }, true);
}

// Take damage
// ダメ�`ジ�I尖
void Player::UnderAttack(int damage) {
    CharacterBase::UnderAttack(damage);
}

// Restore HP
// HPを指��
void Player::AddHP() {
    CharacterBase::SetHP(ConfigManager::GetInstance().GetHealthPackHealAmount());
}

// Shutdown: stop fire timer safely
// シャットダウン�紺k符タイマ�`を芦畠に唯峭
void Player::Shutdown() {
    if (fireTimer) {
        fireTimer->Stop();
        fireTimer.reset();
    }
}
