#pragma once

class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class IHealthPackSystem;

// System for handling all in-game collisions
// ゲーム内の衝突判定を処理するシステム
class CollisionSystem
{
public:
    // Handle collisions between player, bullets, enemies, and health packs
    // プレイヤー、弾、敵、回復アイテム間の衝突を処理
    void HandleCollision(
        IPlayerSystem* ps,
        IBulletSystem* bs,
        IEnemySystem* es,
        IHealthPackSystem* hp);
};
