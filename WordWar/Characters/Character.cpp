#include "Character.h"

// Constructor: initialize position, HP, speed, symbol, etc.
// コンストラクタ：位置、HP、スピード、シンボルなどを初期化
CharacterBase::CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead, int attackPower)
    : x(x),
    y(y),
    hp(hp),
    maxHP(hp),
    speed(speed),
    symbol(symbol),
    isDead(isDead),
    attackPower(attackPower)
{
}

// Destructor
// デストラクタ
CharacterBase::~CharacterBase() {}

// Get X coordinate
// X座標取得
int CharacterBase::GetX() const { return x; }

// Get Y coordinate
// Y座標取得
int CharacterBase::GetY() const { return y; }

// Get HP
// HP取得
int CharacterBase::GetHP() const { return hp; }

// Get attack power
// 攻撃力取得
int CharacterBase::GetAttackPower() const { return attackPower; }

// Get symbol character
// 表示文字取得
char CharacterBase::GetSymbol() const { return symbol; }

// Get alive/dead flag
// 生死状態取得
bool CharacterBase::GetIsDead() const { return isDead; }

// Set X coordinate
// X座標設定
void CharacterBase::SetX(int newX) { x = newX; }

// Set Y coordinate
// Y座標設定
void CharacterBase::SetY(int newY) { y = newY; }

// Add HP (max capped)
// HP加算（最大HPを超えない）
void CharacterBase::SetHP(int addedHP)
{
    if (hp + addedHP > maxHP) {
        hp = maxHP;
    }
    else {
        hp += addedHP;
    }
}

// Take damage and update dead flag
// ダメージ処理＆死亡判定
void CharacterBase::UnderAttack(int damage)
{
    hp -= damage;
    SetIsDead(hp <= 0);
}

// Set alive/dead flag
// 生死状態設定
void CharacterBase::SetIsDead(bool newState)
{
    isDead = newState;
}
