#include "Character.h"

CharacterBase::CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead, int attackPower)
    :
    x(x),
    y(y),
    hp(hp),
    maxHP(hp),
    speed(speed),
    symbol(symbol),
    isDead(isDead),
    attackPower(attackPower)
{}

CharacterBase::~CharacterBase()
{
}

// Get XY, HP, Attack power, symbol, dead flag
// XY、HP、座標、攻撃力、表示文字、生死状態取得
int CharacterBase::GetX() const
{
    return x;
}

int CharacterBase::GetY() const
{
    return y;
}

int CharacterBase::GetHP() const
{
    return hp;
}

int CharacterBase::GetAttackPower() const
{
    return attackPower;
}

char CharacterBase::GetSymbol() const
{
    return symbol;
}

bool CharacterBase::GetIsDead() const
{
    return isDead;
}

// Set XY
// XY　座標設定
void CharacterBase::SetX(int newX)
{    
    x = newX;
}
void CharacterBase::SetY(int newY)
{
    y = newY;
}

// Add HP (not exceed max)
// HP加算（最大HPを超えない）
void CharacterBase::SetHP(int addedHP)
{
    if (hp + addedHP > maxHP)
    {
        hp = maxHP;
    }
    else {
        hp += addedHP;
    }
}

// Take damage
// ダメージ処理
void CharacterBase::UnderAttack(int damage)
{
    hp -= damage;
    SetIsDead(hp <= 0);
}

// Set dead flag
// 生死状態設定
void CharacterBase::SetIsDead(bool newState)
{
    isDead = newState;
}