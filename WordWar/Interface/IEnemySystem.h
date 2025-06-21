#pragma once
#include "../Characters/Enemies/Enemy.h"

#include <vector>
#include <memory>

// Interface for enemy system
// �������ƥ��å��󥿩`�ե��`��
class IEnemySystem
{
public:
    // Spawn new enemies at specified position
    // ָ��λ�ä˔�������
    virtual void SpawnEnemies(int x, int y, IPlayerSystem* p) = 0;

    // Get all active enemies
    // �F�ڤ�ȫ�ƤΔ���ȡ��
    virtual const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const = 0;

    // Add to eliminated enemy count
    // �����������
    virtual void AddEliminatedEnemyCount(int count) = 0;

    // Get total eliminated enemy count
    // ���Ɯg�ߤΔ�����ȡ��
    virtual const int GetEliminatedEnemyCount() const = 0;

    virtual ~IEnemySystem() {};
};
