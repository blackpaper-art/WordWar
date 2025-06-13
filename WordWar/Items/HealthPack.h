#pragma once
#include "../Characters/Character.h"

class TimerManager;

class HealthPack : public CharacterBase
{
public:
	HealthPack(TimerManager* tm);
	~HealthPack();

private:
	TimerManager* timerManager;
};