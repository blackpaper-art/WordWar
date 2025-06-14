#pragma once

#include "../Character.h"
#include "../../Characters/Player.h"

// Enemy character
// ������饯���`
class Enemy :public CharacterBase
{
public:
	Enemy(int x, int y, IPlayerSystem* ps);
	~Enemy();

	// Can move or not
	// �ƄӤǤ��뤫
	bool CanMove(float deltaTime);

	// Predict next position
	// �Τ�λ�ä���y
	void PredicNextPos(int& outX, int& outY) const;

private:
	IPlayerSystem* playerSystem;	// Player info  �ץ쥤��`���
	float moveInterval;				// �Ƅ��g��
	float timeAccumulator;			// �r�g�۷e
};