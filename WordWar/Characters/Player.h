#pragma once
#include "Character.h"
#include "../Interface/IPlayerSystem.h"
#include "../Managers/TimerManager.h"

class IBulletSystem;
class TimerManager;

class Player : public CharacterBase, public IPlayerSystem
{
public:
	Player(int x, int y, IBulletSystem* bs, TimerManager* tm);
	~Player();

	void Update(char input);

	//interfaces
	int GetX() const override;
	int GetY() const;
	int GetHP() const override;
	char GetSymbol() const override;
	int GetPlayerLevel() override;
	int GetPlayerBulletLevel() override;

	void AddKillCount(int count) override;
	void TryLevelUp() override;
	void FireBullets(int bLevel, int rate) override;
	void UnderAttack(int damage) override;
	void AddHP() override;

private:
	IBulletSystem* bulletSystem;
	TimerManager* timerManager;

	int bulletLevel;
	int bulletDir;

	//EXP relevant
	int level;
	int killCount;
	int nextLevelKills;
};