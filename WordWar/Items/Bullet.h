#pragma once
#include "../Characters/Character.h"

// Enum for bullet move direction
// 弾の移動方向を示す列挙型
enum class MoveDir {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

// Bullet class derived from CharacterBase
// CharacterBase を継承した弾クラス
class Bullet : public CharacterBase
{
public:
    // Constructor: create bullet with direction and level
    // コンストラクタ：方向とレベルを指定して弾を生成
    Bullet(int x, int y, MoveDir dir, int bulletLevel);

    ~Bullet(); // Destructor / デストラクタ

    // Update bullet position
    // 弾の位置を更新
    void Update(float deltaTime);

    // Check if bullet is out of field
    // 弾がフィールド外か確認
    bool GetIsOutOfField();

    // Check if bullet can move this frame
    // このフレームで弾が移動可能か確認
    bool CanMove(float deltaTime);
private:
    MoveDir direction;    // Bullet direction / 弾の方向
    bool isOutOfField;    // Out of field flag / フィールド外フラグ

    float moveInterval;   // Movement interval / 移動間隔
    float timeAccumulator; // Time accumulator for movement / 移動用時間累積
};