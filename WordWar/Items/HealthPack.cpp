#include "HealthPack.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize health pack properties
// コンストラクタ：回復アイテムの初期化
HealthPack::HealthPack(int x, int y)
    : CharacterBase(x, y, 1, 0, ConfigManager::GetInstance().GetHealthPackSymbol()[0], false, 0)
{
}

// Destructor
// デストラクタ
HealthPack::~HealthPack() {}

// Get symbol character
// 表示文字を取得
char HealthPack::GetSymbol() const
{
    return CharacterBase::GetSymbol();
}
