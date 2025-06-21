#include "Character.h"

// Constructor: initialize position, HP, speed, symbol, etc.
// ���󥹥ȥ饯����λ�á�HP�����ԩ`�ɡ�����ܥ�ʤɤ���ڻ�
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
// �ǥ��ȥ饯��
CharacterBase::~CharacterBase() {}

// Get X coordinate
// X����ȡ��
int CharacterBase::GetX() const { return x; }

// Get Y coordinate
// Y����ȡ��
int CharacterBase::GetY() const { return y; }

// Get HP
// HPȡ��
int CharacterBase::GetHP() const { return hp; }

// Get attack power
// ������ȡ��
int CharacterBase::GetAttackPower() const { return attackPower; }

// Get symbol character
// ��ʾ����ȡ��
char CharacterBase::GetSymbol() const { return symbol; }

// Get alive/dead flag
// ����״�Bȡ��
bool CharacterBase::GetIsDead() const { return isDead; }

// Set X coordinate
// X�����O��
void CharacterBase::SetX(int newX) { x = newX; }

// Set Y coordinate
// Y�����O��
void CharacterBase::SetY(int newY) { y = newY; }

// Add HP (max capped)
// HP���㣨���HP�򳬤��ʤ���
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
// ����`���I�������ж�
void CharacterBase::UnderAttack(int damage)
{
    hp -= damage;
    SetIsDead(hp <= 0);
}

// Set alive/dead flag
// ����״�B�O��
void CharacterBase::SetIsDead(bool newState)
{
    isDead = newState;
}
