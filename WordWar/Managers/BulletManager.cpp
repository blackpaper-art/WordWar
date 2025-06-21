#include "../Managers/BulletManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

// Constructor
// コンストラクタ
BulletManager::BulletManager() {}

// Destructor
// デストラクタ
BulletManager::~BulletManager() {}

// Spawn a new bullet with level info
// レベル情報付きで新しい弾を生成
void BulletManager::SpawnBullet(int x, int y, MoveDir dir, int bulletLevel)
{
    bullets.push_back(std::make_unique<Bullet>(x, y, dir, bulletLevel));
}

// Update all bullets and remove dead/out-of-field ones
// 全ての弾を更新し、死んだものや画面外のものを削除
void BulletManager::Update(float deltaTime)
{
    auto it = bullets.begin();
    while (it != bullets.end())
    {
        // Remove if null
        // nullptrなら削除
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
// 現在の弾リストを取得
const std::vector<std::unique_ptr<Bullet>>& BulletManager::GetAllBullets() const
{
    return bullets;
}

// Get current bullet count
// 弾の数を取得
int BulletManager::GetBulletCount() const
{
    return static_cast<int>(bullets.size());
}
