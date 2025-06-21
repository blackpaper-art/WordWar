#pragma once
#include "../Characters/Character.h"

// Health pack item that restores player HP
// プレイヤーのHPを回復する回復アイテムクラス
class HealthPack : public CharacterBase
{
public:
    HealthPack(int x, int y); // Constructor / コンストラクタ
    ~HealthPack();            // Destructor / デストラクタ

    char GetSymbol() const;   // Get symbol character / 表示文字を取得
};
