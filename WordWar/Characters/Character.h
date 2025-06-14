#pragma once

// Position struct
// 座標構造体
struct Position
{
	int x, y;
};

// Base class for all characters
// キャラクター基底クラス
class CharacterBase
{
public:
	CharacterBase(int x, int y, int hp, int speed, char symbol, bool isDead, int attackPower);
	~CharacterBase();

	// Get XY, HP, Attack power, symbol, dead flag
	// XY、HP、座標、攻撃力、表示文字、生死状態取得
	int GetX() const;
	int GetY() const;
	int GetHP() const;
	int GetAttackPower() const;
	char GetSymbol() const;
	bool GetIsDead() const;

	// Set X and Y coordinate
	// X Y座標設定
	void SetX(int newX);
	void SetY(int newY);

	// Add to HP (max capped)
	// HP加算（最大値制限）
	void SetHP(int addedHP);

	// Take damage
	// ダメージ処理
	void UnderAttack(int damage);

private:
	int x, y;                 // Position			// 座標
	int hp;                   // Current HP			// 現在HP
	int maxHP;                // Max HP				// 最大HP
	int speed;                // Speed				// スピード
	int attackPower;          // Attack power		// 攻撃力
	char symbol;              // Symbol character	// 表示文字
	bool isDead;              // Alive/Dead flag	// 生死状態

	void SetIsDead(bool newState);
};