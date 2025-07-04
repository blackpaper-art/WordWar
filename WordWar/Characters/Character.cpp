#include "Character.h"

// Constructor: initialize position, HP, speed, symbol, etc.
// コンストラクタ�採志叩�HP、スピ�`ド、シンボルなどを兜豚晒
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
// X恙�鉾ゝ�
int CharacterBase::GetX() const { return x; }

// Get Y coordinate
// Y恙�鉾ゝ�
int CharacterBase::GetY() const { return y; }

// Get HP
// HP函誼
int CharacterBase::GetHP() const { return hp; }

// Get attack power
// 好�珍θゝ�
int CharacterBase::GetAttackPower() const { return attackPower; }

// Get symbol character
// 燕幣猟忖函誼
char CharacterBase::GetSymbol() const { return symbol; }

// Get alive/dead flag
// 伏棒彜�B函誼
bool CharacterBase::GetIsDead() const { return isDead; }

// Set X coordinate
// X恙�穆O協
void CharacterBase::SetX(int newX) { x = newX; }

// Set Y coordinate
// Y恙�穆O協
void CharacterBase::SetY(int newY) { y = newY; }

// Add HP (max capped)
// HP紗麻��恷寄HPを階えない��
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
// ダメ�`ジ�I尖�λ斥�登協
void CharacterBase::UnderAttack(int damage)
{
    hp -= damage;
    SetIsDead(hp <= 0);
}

// Set alive/dead flag
// 伏棒彜�B�O協
void CharacterBase::SetIsDead(bool newState)
{
    isDead = newState;
}
