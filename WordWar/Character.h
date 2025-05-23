#pragma once

struct Position
{
	int x, y;
};

class CharacterBase
{
public:
	CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead);
	~CharacterBase();

	void Initialize(int x, int y, int hp, int speed, char symbol, bool isDead);
	
	int GetX() const;
	int GetY() const;
	int GetHP() const;
	char GetSymbol() const;
	bool GetIsDead() const;

	void SetX(int newX);
	void SetY(int newY);
	void SetIsDead(bool newState);

	Position ShowInfo();

private:
	int x,y;
	int hp;
	int speed;
	char symbol;
	bool isDead;
};