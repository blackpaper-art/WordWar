#pragma once
#include "../Items/Bullet.h"
#include "../Interface/IBulletSystem.h"

#include <vector>
#include <memory>

// Manager for spawning and managing bullets
// �������ɤȹ�����Ф��ޥͩ`����`���饹
class BulletManager : public IBulletSystem
{
public:
    BulletManager();   // Constructor / ���󥹥ȥ饯��
    ~BulletManager();  // Destructor / �ǥ��ȥ饯��

    // Spawn a bullet with level info
    // ��٥���󸶤��Ǐ�������
    void SpawnBullet(int x, int y, MoveDir dir, int bulletLevel) override;

    // Update all bullets
    // �������
    void Update(float deltaTime);

    // Get all bullets
    // ȫ�ƤΏ���ȡ��
    const std::vector<std::unique_ptr<Bullet>>& GetAllBullets() const override;

    // Get bullet count
    // ��������ȡ��
    int GetBulletCount() const override;

private:
    std::vector<std::unique_ptr<Bullet>> bullets; // Active bullets / �F�ڤΏ��ꥹ��
};
