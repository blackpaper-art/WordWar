#include "../Characters/Character.h"
#include "../Managers/TimerManager.h"
#include "HealthPack.h"

#include <set>

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

HealthPack::HealthPack(TimerManager* tm)
	:
	CharacterBase(rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT, 1, 0, 'H', false, 0),
	timerManager(tm)
{
	//Spawn HealthPack at random position in 1 mins 60000ms
	timerManager->SetTimer(1000 * 60, [this] {

		int randomX, randomY;

		randomX = rand() % FIELD_WIDTH;
		randomY = rand() % FIELD_HEIGHT;

		SetX(randomX);
		SetY(randomY);
		}, true);
}

HealthPack::~HealthPack()
{
}
