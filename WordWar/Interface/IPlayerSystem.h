#pragma once
#include "../Characters/Player.h"

#include <vector>
#include <memory>

class IPlayerSystem
{
public:
	//Get functions
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
	virtual int GetHP() const = 0;
	virtual char GetSymbol() const = 0;
	virtual int GetPlayerLevel() = 0;
	//Get debug info
	virtual int GetPlayerBulletLevel() = 0;

	//Changeable function
	virtual void UnderAttack(int damage) = 0;
	virtual void FireBullets(int bLevel, int rate) = 0;
	virtual void AddKillCount(int count) = 0;
	virtual void TryLevelUp() = 0;
	virtual void AddHP() = 0;

	virtual ~IPlayerSystem() {};
};