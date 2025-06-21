#include "Bullet.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

// Constructor: initialize bullet with level and direction
// コンストラクタ：弾をレベルと方向で初期化
Bullet::Bullet(int x, int y, MoveDir dir, int bulletLevel)
    : CharacterBase(x, y, bulletLevel, 1, '.', false, 1),
    direction(dir),
    isOutOfField(false),
    moveInterval(100.0f),
    timeAccumulator(0.0f)
{
}

// Destructor
// デストラクタ
Bullet::~Bullet() {}

// Update bullet position based on direction and speed
// 方向と速度に基づいて弾の位置を更新
void Bullet::Update(float deltaTime)
{
    if (!this->GetIsDead() && CanMove(deltaTime))
    {
        int newX = GetX(), newY = GetY();

        // Update position by direction
        // 方向に応じて位置を変更
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
        // フィールド外に出たか判定
        if (newX < 0 || newX >= FIELD_WIDTH || newY < 0 || newY >= FIELD_HEIGHT)
        {
            isOutOfField = true;
            return;
        }

        // Move to new position
        // 新しい位置に移動
        SetY(newY);
        SetX(newX);
    }
}

// Check if bullet is out of field
// 弾がフィールド外か確認
bool Bullet::GetIsOutOfField()
{
    return isOutOfField;
}

// Check if bullet can move this frame
// このフレームで弾が移動可能か確認
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
