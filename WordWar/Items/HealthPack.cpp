#include "HealthPack.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize health pack properties
// ���󥹥ȥ饯�����؏ͥ����ƥ�γ��ڻ�
HealthPack::HealthPack(int x, int y)
    : CharacterBase(x, y, 1, 0, ConfigManager::GetInstance().GetHealthPackSymbol()[0], false, 0)
{
}

// Destructor
// �ǥ��ȥ饯��
HealthPack::~HealthPack() {}

// Get symbol character
// ��ʾ���֤�ȡ��
char HealthPack::GetSymbol() const
{
    return CharacterBase::GetSymbol();
}
