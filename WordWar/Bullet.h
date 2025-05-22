#pragma once
#include "Character.h"

class Bullet : public CharacterBase
{
public:
	Bullet(int x, int y);
	~Bullet();

	void Update();
private:
};