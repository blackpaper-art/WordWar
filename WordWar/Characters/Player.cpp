#include "Player.h"
#include "../Interface/IBulletSystem.h"
#include "../Items/Bullet.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize player properties
// ���󥹥ȥ饯�����ץ쥤��`�γ��ڂ����O��
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
// �ǥ��ȥ饯�����k�䥿���ީ`�������ֹͣ
Player::~Player()
{
    if (fireTimer) {
        fireTimer->isActive = false;
    }
}

// Update player position based on input
// �����ˏꤸ�ƥץ쥤��`��λ�ä����
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
// ����������㤷����٥륢�å��ж�
void Player::AddKillCount(int count)
{
    killCount += count;
    TryLevelUp();
}

// Try to level up based on kill count
// �������ˏꤸ�ƥ�٥륢�åפ��ж�
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
        // ��GetPlayerBulletUpBaseLevel���Υ�٥뤴�Ȥˏ���٥�򥢥å�
        if (level % ConfigManager::GetInstance().GetPlayerBulletUpBaseLevel() == 0) {
            bulletLevel++;
        }

		// Update fire timer interval based on new level
		// �¤�����٥�ˏꤸ�ưk�䥿���ީ`���g�������
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
// �ץ쥤��`��٥�ˏꤸ�ƶ෽��ˏ���k��
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
        // ȫ����ˏ�������
        for (const auto& dir : directions)
        {
            bulletSystem->SpawnBullet(CharacterBase::GetX(), CharacterBase::GetY(), dir, bulletLevel);
        }
    }
}

// Interfaces implementation

// Get player level
// �ץ쥤��`��٥�ȡ��
int Player::GetPlayerLevel() { return level; }

// Get bullet level
// ����٥�ȡ��
int Player::GetPlayerBulletLevel() { return bulletLevel; }

// Get remaining EXP to next level
// �Υ�٥�ޤǤ�EXPȡ��
int Player::GetEXPRemain() { return nextLevelKills - killCount; }

// Get X coordinate
// X����ȡ��
int Player::GetX() const { return CharacterBase::GetX(); }

// Get Y coordinate
// Y����ȡ��
int Player::GetY() const { return CharacterBase::GetY(); }

// Get HP
// HPȡ��
int Player::GetHP() const { return CharacterBase::GetHP(); }

// Get symbol character
// ��ʾ����ȡ��
char Player::GetSymbol() const { return CharacterBase::GetSymbol(); }

// Initialize player and start fire timer
// �ץ쥤��`���ڻ��Ȱk�䥿���ީ`�_ʼ
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
// ����`���I��
void Player::UnderAttack(int damage) {
    CharacterBase::UnderAttack(damage);
}

// Restore HP
// HP��؏�
void Player::AddHP() {
    CharacterBase::SetHP(ConfigManager::GetInstance().GetHealthPackHealAmount());
}

// Shutdown: stop fire timer safely
// ����åȥ����󣺰k�䥿���ީ`��ȫ��ֹͣ
void Player::Shutdown() {
    if (fireTimer) {
        fireTimer->Stop();
        fireTimer.reset();
    }
}
