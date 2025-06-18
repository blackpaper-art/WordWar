#pragma once
#include "TimerManager.h"

#include <stdio.h>
#include <memory>
#include <vector>

#define X_WALL 'X'
#define Y_WALL 'Y'
#define FIELD_NULL ' '

class EnemyManager;
class TimerManager;
class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class IHealthPackSystem;


class FieldManager : public std::enable_shared_from_this<FieldManager>
{
public:
	std::shared_ptr<TimerHandle> countDownTimer;

	FieldManager();
	~FieldManager();

	const int GetFieldWidth() { return fieldWidth; }
	const int GetFieldHeight(){ return fieldHeight; }

	void InitializeManagers(IPlayerSystem* ps, IEnemySystem* es, IBulletSystem* bs, IHealthPackSystem* hps, TimerManager* tm);
	void Update(float deltaTime);
	void DrawField();
	void ShowDebugInfo(char input);
private:

	IEnemySystem* enemySystem;
	IPlayerSystem* playerSystem;
	IBulletSystem* bulletSystem;
	IHealthPackSystem* healthPackSystem;

	int fieldWidth;
	int fieldHeight;
	std::vector<std::vector<char>> fieldBuffer;

	void CountDownTimer();
	int countDownTime;
	float myDeltaTime;

	bool showDebugMessage;
};
