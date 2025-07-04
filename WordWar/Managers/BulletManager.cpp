#include "../Managers/BulletManager.h"

// Constructor
// コンストラクタ
BulletManager::BulletManager() {}

// Destructor
// デストラクタ
BulletManager::~BulletManager() {}

// Spawn a new bullet with level info
// レベル秤�鷂兇�で仟しい�､鯢�撹
void BulletManager::SpawnBullet(int x, int y, MoveDir dir, int bulletLevel)
{
    bullets.push_back(std::make_unique<Bullet>(x, y, dir, bulletLevel));
}

// Update all bullets and remove dead/out-of-field ones
// 畠ての�､鮓�仟し、棒んだものや鮫中翌のものを��茅
void BulletManager::Update(float deltaTime)
{
    auto it = bullets.begin();
    while (it != bullets.end())
    {
        // Remove if null
        // nullptrなら��茅
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
// �F壓の�･螢好箸鯣ゝ�
const std::vector<std::unique_ptr<Bullet>>& BulletManager::GetAllBullets() const
{
    return bullets;
}

// Get current bullet count
// �､諒�を函誼
int BulletManager::GetBulletCount() const
{
    return static_cast<int>(bullets.size());
}
