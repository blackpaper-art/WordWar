#include "HealthPack.h"

HealthPack::HealthPack(int x, int y)
    : CharacterBase(x, y, 1, 0, '+', false, 0)
{}

HealthPack::~HealthPack() {}

char HealthPack::GetSymbol() const
{
    return CharacterBase::GetSymbol();
}