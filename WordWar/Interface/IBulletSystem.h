#pragma once

#include "../Items/Bullet.h"

#include <vector>
#include <memory>

// Interface for bullet system
// �������ƥ��å��󥿩`�ե��`��
class IBulletSystem
{
public:
    // Spawn a bullet with specified direction and level
    // ָ����������ȥ�٥�Ǐ�������
    virtual void SpawnBullet(int x, int y, MoveDir dir, int bulletLevel) = 0;

    // Get all active bullets
    // �F�ڤ�ȫ�ƤΏ���ȡ��
    virtual const std::vector<std::unique_ptr<Bullet>>& GetAllBullets() const = 0;

    // Get current bullet count
    // ���ξt����ȡ��
    virtual int GetBulletCount() const = 0;

    virtual ~IBulletSystem() {}
};
