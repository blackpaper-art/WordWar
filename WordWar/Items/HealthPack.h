#pragma once
#include "../Characters/Character.h"

class HealthPack : public CharacterBase
{
public:
    HealthPack(int x, int y);
    ~HealthPack();

    char GetSymbol() const;
};
