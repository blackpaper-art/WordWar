#pragma once
#include "../Items/Bullet.h"
#include "../Interface/IBulletSystem.h"

#include <vector>
#include <memory>

// Manager for spawning and managing bullets
// 弾の生成と管理を行うマネージャークラス
class BulletManager : public IBulletSystem
{
public:
    BulletManager();   // Constructor / コンストラクタ
    ~BulletManager();  // Destructor / デストラクタ

    // Spawn a bullet with level info
    // レベル情報付きで弾を生成
    void SpawnBullet(int x, int y, MoveDir dir, int bulletLevel) override;

    // Update all bullets
    // 弾を更新
    void Update(float deltaTime);

    // Get all bullets
    // 全ての弾を取得
    const std::vector<std::unique_ptr<Bullet>>& GetAllBullets() const override;

    // Get bullet count
    // 弾の数を取得
    int GetBulletCount() const override;

private:
    std::vector<std::unique_ptr<Bullet>> bullets; // Active bullets / 現在の弾リスト
};
