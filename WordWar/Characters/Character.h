#pragma once

struct Position
{
	int x, y;
};

class CharacterBase
{
public:
	CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead, int attackPower);
	~CharacterBase();
	
	int GetX() const;
	int GetY() const;
	int GetHP() const;
	int GetAttackPower() const;
	char GetSymbol() const;
	bool GetIsDead() const;

	void SetX(int newX);
	void SetY(int newY);
	void UnderAttack(int damage);

	Position ShowInfo();

private:
	int x,y;
	int hp;
	int speed;
	int attackPower;
	char symbol;
	bool isDead;

	void SetIsDead(bool newState);
};