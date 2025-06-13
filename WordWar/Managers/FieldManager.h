#pragma once
#include <stdio.h>

#define X_WALL 'X'
#define Y_WALL 'Y'
#define FIELD_NULL ' '

class EnemyManager;
class Player;
class TimerManager;
class IBulletSystem;
class IEnemySystem;

class FieldManager
{
public:
	FieldManager();
	~FieldManager();

	const int GetFieldWidth() { return fieldWidth; }
	const int GetFieldHeight(){ return fieldHeight; }

	char GetField(int x, int y);
	void SetField(int x, int y, char intern);
	void InitializeManagers(Player* p, TimerManager* tm, IEnemySystem* es, IBulletSystem* bs);
	void Update(float deltaTime);
	void DrawField();
private:
	Player* player;

	TimerManager* timerManager;
	IEnemySystem* enemySystem;
	IBulletSystem* bulletSystem;

	static const int fieldWidth = 16 * 3;
	static const int fieldHeight = 9 * 3;
	char field[fieldHeight][fieldWidth];

	void CountDownTimer();
	int countDownTime;
	float myDeltaTime;
};
