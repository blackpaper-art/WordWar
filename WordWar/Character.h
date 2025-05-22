#pragma once

class CharacterBase
{
public:
	CharacterBase(int x, int y, int hp, int speed, char symbol);
	~CharacterBase();

	void Initialize(int x, int y, int hp, int speed, char symbol);

	int GetX() const;
	int GetY() const;
	int GetHP() const;
	char GetSymbol() const;

	void SetX(int newX);
	void SetY(int newY);

private:
	int x,y;
	int hp;
	int speed;
	char symbol;
};