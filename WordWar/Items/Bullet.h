#pragma once
#include "../Characters/Character.h"

enum class MoveDir {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

class Bullet : public CharacterBase
{
public:
	Bullet(int x, int y, MoveDir dir, int bulletLevel);
	~Bullet();

	void Update(float deltaTime);
    bool GetIsOutOfField();
    bool CanMove(float deltaTime);
private:
    MoveDir direction;
    bool isOutOfField;

    float moveInterval;
    float timeAccumulator;
};