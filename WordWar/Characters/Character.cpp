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
// XY��HP�����ˡ�����������ʾ���֡�����״�Bȡ��
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
// XY�������O��
void CharacterBase::SetX(int newX)
{    
    x = newX;
}
void CharacterBase::SetY(int newY)
{
    y = newY;
}

// Add HP (not exceed max)
// HP���㣨���HP�򳬤��ʤ���
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
// ����`���I��
void CharacterBase::UnderAttack(int damage)
{
    hp -= damage;
    SetIsDead(hp <= 0);
}

// Set dead flag
// ����״�B�O��
void CharacterBase::SetIsDead(bool newState)
{
    isDead = newState;
}