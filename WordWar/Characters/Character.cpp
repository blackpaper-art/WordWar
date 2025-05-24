#include "Character.h"

CharacterBase::CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead)
    : 
    x(x), 
    y(y), 
    hp(hp), 
    speed(speed),
    symbol(symbol),
    isDead(isDead)
{}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Initialize(int x, int y, int hp, int speed, char symbol, bool isDead)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->speed = speed;
    this->symbol = symbol;
    this->isDead = isDead;
}

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

char CharacterBase::GetSymbol() const
{
    return symbol;
}

bool CharacterBase::GetIsDead() const
{
    return isDead;
}

void CharacterBase::SetX(int newX)
{
    x = newX;
}

void CharacterBase::SetY(int newY)
{
    y = newY;
}

void CharacterBase::SetIsDead(bool newState)
{
    isDead = newState;
}

Position CharacterBase::ShowInfo() {
    return { GetX(), GetY() };
}
