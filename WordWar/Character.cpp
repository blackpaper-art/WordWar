#include "Character.h"

CharacterBase::CharacterBase(int x, int y, int hp, int speed, char symbol)
    : 
    x(x), 
    y(y), 
    hp(hp), 
    speed(speed),
    symbol(symbol)
{}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Initialize(int x, int y, int hp, int speed, char symbol)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->speed = speed;
    this->symbol = symbol;
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

void CharacterBase::SetX(int newX)
{
    x = newX;
}

void CharacterBase::SetY(int newY)
{
    y = newY;
}

