#pragma once

#include "../Character.h"
#include "../../Characters/Player.h"

// Enemy character
// ”³¥­¥ã¥é¥¯¥¿©`
class Enemy :public CharacterBase
{
public:
	Enemy(int x, int y, IPlayerSystem* ps);
	~Enemy();

	// Can move or not
	// ÒÆ„Ó¤Ç¤­¤ë¤«
	bool CanMove(float deltaTime);

	// Predict next position
	// ´Î¤ÎÎ»ÖÃ¤òÓèœy
	void PredicNextPos(int& outX, int& outY) const;

private:
	IPlayerSystem* playerSystem;	// Player info  ¥×¥ì¥¤¥ä©`Çéˆó
	float moveInterval;				// ÒÆ„Óég¸ô
	float timeAccumulator;			// •régÀÛ·e
};