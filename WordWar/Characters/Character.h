#pragma once

// Position struct
// ���˘�����
struct Position
{
	int x, y;
};

// Base class for all characters
// ����饯���`���ץ��饹
class CharacterBase
{
public:
	CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead, int attackPower);
	~CharacterBase();

	// Get XY, HP, Attack power, symbol, dead flag
	// XY��HP�����ˡ�����������ʾ���֡�����״�Bȡ��
	int GetX() const;
	int GetY() const;
	int GetHP() const;
	int GetAttackPower() const;
	char GetSymbol() const;
	bool GetIsDead() const;

	// Set X and Y coordinate
	// X Y�����O��
	void SetX(int newX);
	void SetY(int newY);

	// Add to HP (max capped)
	// HP���㣨������ޣ�
	void SetHP(int addedHP);

	// Take damage
	// ����`���I��
	void UnderAttack(int damage);

private:
	int x, y;                 // Position			// ����
	int hp;                   // Current HP			// �F��HP
	int maxHP;                // Max HP				// ���HP
	int speed;                // Speed				// ���ԩ`��
	int attackPower;          // Attack power		// ������
	char symbol;              // Symbol character	// ��ʾ����
	bool isDead;              // Alive/Dead flag	// ����״�B

	void SetIsDead(bool newState);
};