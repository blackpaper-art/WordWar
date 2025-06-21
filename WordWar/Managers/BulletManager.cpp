#include "../Managers/BulletManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

// Constructor
// ���󥹥ȥ饯��
BulletManager::BulletManager() {}

// Destructor
// �ǥ��ȥ饯��
BulletManager::~BulletManager() {}

// Spawn a new bullet with level info
// ��٥���󸶤����¤�����������
void BulletManager::SpawnBullet(int x, int y, MoveDir dir, int bulletLevel)
{
    bullets.push_back(std::make_unique<Bullet>(x, y, dir, bulletLevel));
}

// Update all bullets and remove dead/out-of-field ones
// ȫ�ƤΏ�����¤����������Τ仭����Τ�Τ�����
void BulletManager::Update(float deltaTime)
{
    auto it = bullets.begin();
    while (it != bullets.end())
    {
        // Remove if null
        // nullptr�ʤ�����
        if (it->get() == nullptr) {
            it = bullets.erase(it);
            continue;
        }

        (*it)->Update(deltaTime);
        if ((*it)->GetIsDead() || (*it)->GetIsOutOfField())
        {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

// Get all active bullets
// �F�ڤΏ��ꥹ�Ȥ�ȡ��
const std::vector<std::unique_ptr<Bullet>>& BulletManager::GetAllBullets() const
{
    return bullets;
}

// Get current bullet count
// ��������ȡ��
int BulletManager::GetBulletCount() const
{
    return static_cast<int>(bullets.size());
}
