#pragma once
#include "../Characters/Player.h"

#include <vector>
#include <memory>

// Interface for player system
// �ץ쥤��`�����ƥ��å��󥿩`�ե��`��
class IPlayerSystem
{
public:
    // Get functions
    // �ץ쥤��`���ȡ��ϵ
    virtual int GetX() const = 0;         // Get X coordinate / X����ȡ��
    virtual int GetY() const = 0;         // Get Y coordinate / Y����ȡ��
    virtual int GetHP() const = 0;         // Get HP / HPȡ��
    virtual char GetSymbol() const = 0;   // Get symbol character / ��ʾ����ȡ��
    virtual int GetPlayerLevel() = 0;     // Get player level / �ץ쥤��`��٥�ȡ��
    virtual int GetEXPRemain() = 0;       // Get remaining EXP to next level / �Υ�٥�ޤǤ�EXPȡ��

    // Get debug info
    // �ǥХå������ȡ��
    virtual int GetPlayerBulletLevel() = 0; // Get bullet level / ����٥�ȡ��

    // Changeable functions
    // �ץ쥤��`״�B���ϵ
    virtual void Initialize() = 0;           // Initialize player / ���ڻ�
    virtual void UnderAttack(int damage) = 0; // Take damage / ����`�����ܤ���
    void FireBullets(int bLevel, int rate);  // Fire bullets / ����k��
    virtual void AddKillCount(int count) = 0; // Add kill count / ����������
    virtual void TryLevelUp() = 0;            // Try to level up / ��٥륢�å��ж�
    virtual void AddHP() = 0;                  // Restore HP / HP�؏�

    virtual ~IPlayerSystem() {};
};
