#pragma once
#include "../Characters/Character.h"

// Health pack item that restores player HP
// �ץ쥤��`��HP��؏ͤ���؏ͥ����ƥ९�饹
class HealthPack : public CharacterBase
{
public:
    HealthPack(int x, int y); // Constructor / ���󥹥ȥ饯��
    ~HealthPack();            // Destructor / �ǥ��ȥ饯��

    char GetSymbol() const;   // Get symbol character / ��ʾ���֤�ȡ��
};
