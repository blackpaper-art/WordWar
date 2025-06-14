#pragma once
#include "../Characters/Character.h"

class TimerManager;

class HealthPack : public CharacterBase
{
public:
	std::shared_ptr<TimerHandle> healthPackSpawnTimer;

	HealthPack(TimerManager* tm);
	~HealthPack();
};