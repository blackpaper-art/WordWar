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
	Bullet(int x, int y, MoveDir dir);
	~Bullet();

	void Update();
    bool GetIsOutOfField();

private:
    MoveDir direction;
    bool isOutOfField;
};