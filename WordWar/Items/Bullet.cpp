#include "Bullet.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize bullet with level and direction
// コンストラクタ���､鬟譽戰襪鳩熟鬚燃�豚晒
Bullet::Bullet(int x, int y, MoveDir dir, int bulletLevel)
    : CharacterBase
    (
        x, y, bulletLevel, 1,
        ConfigManager::GetInstance().GetBulletSymbol()[0],
        false,
        ConfigManager::GetInstance().GetBulletInitialAP()
    ),
    direction(dir),
    isOutOfField(false),
    moveInterval(ConfigManager::GetInstance().GetBulletMoveInterval()),
    timeAccumulator(0.0f)
{
}

// Destructor
// デストラクタ
Bullet::~Bullet() {}

// Update bullet position based on direction and speed
// 圭�鬚繁拔箸忙�づいて�､領志辰鮓�仟
void Bullet::Update(float deltaTime)
{
    if (!this->GetIsDead() && CanMove(deltaTime))
    {
        int newX = GetX(), newY = GetY();

        // Update position by direction
        // 圭�鬚�鬉犬椴志辰��筝�
        switch (direction)
        {
        case MoveDir::Up:         newY -= 1; break;
        case MoveDir::Down:       newY += 1; break;
        case MoveDir::Left:       newX -= 1; break;
        case MoveDir::Right:      newX += 1; break;
        case MoveDir::UpLeft:     newY += 1; newX -= 2; break;
        case MoveDir::UpRight:    newY += 1; newX += 2; break;
        case MoveDir::DownLeft:   newY -= 1; newX -= 2; break;
        case MoveDir::DownRight:  newY -= 1; newX += 2; break;
        default: break;
        }

        // Check if bullet is out of field
        // フィ�`ルド翌に竃たか登協
        if (newX < 0 || newX >= ConfigManager::GetInstance().GetFieldWidth() || newY < 0 || newY >= ConfigManager::GetInstance().GetFieldHeight())
        {
            isOutOfField = true;
            return;
        }

        // Move to new position
        // 仟しい了崔に卞��
        SetY(newY);
        SetX(newX);
    }
}

// Check if bullet is out of field
// �､�フィ�`ルド翌か�_�J
bool Bullet::GetIsOutOfField()
{
    return isOutOfField;
}

// Check if bullet can move this frame
// このフレ�`ムで�､�卞�喊苗椶��_�J
bool Bullet::CanMove(float deltaTime)
{
    timeAccumulator += deltaTime;
    if (timeAccumulator >= moveInterval)
    {
        timeAccumulator = 0.0f;
        return true;
    }
    return false;
}
