#include "../Interface/IBulletSystem.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"
#include "../Interface/IHealthPackSystem.h"

#include "../Items/HealthPack.h"

#include "CollisionSystem.h"
#include <windows.h> // For Beep()

// Handle all collisions between bullets, enemies, player, and health packs
// 弾、敵、プレイヤー、回復アイテム間の全ての衝突を処理
void CollisionSystem::HandleCollision(
    IPlayerSystem* ps,
    IBulletSystem* bs,
    IEnemySystem* es,
    IHealthPackSystem* hps)
{
    // Prepare hit records
    // 当たり判定の結果を記録
    std::vector<std::pair<Bullet*, Enemy*>> bulletEnemyHits;
    std::vector<Enemy*> playerEnemyHits;

    // Bullet & Enemy collision
    // 弾と敵の衝突
    for (const auto& b : bs->GetAllBullets()) {
        if (!b || b->GetIsDead()) continue;

        for (const auto& e : es->GetAllEnemy()) {
            if (!e || e->GetIsDead()) continue;

            if (b->GetX() == e->GetX() && b->GetY() == e->GetY()) {
                bulletEnemyHits.push_back({ b.get(), e.get() });
                break;
            }
        }
    }

    // Player & Enemy collision
    // プレイヤーと敵の衝突
    for (const auto& e : es->GetAllEnemy()) {
        if (!e || e->GetIsDead()) continue;

        if (ps->GetX() == e->GetX() && ps->GetY() == e->GetY()) {
            playerEnemyHits.push_back(e.get());
            break;
        }
    }

    // Player & HealthPack collision
    // プレイヤーと回復アイテムの衝突
    for (const auto& hp : hps->GetAllHealthPacks()) {
        if (!hp->GetIsDead() && ps->GetX() == hp->GetX() && ps->GetY() == hp->GetY()) {
            hp->UnderAttack(hp->GetHP()); // Mark as used / 使用済みにする
            ps->AddHP();                  // Player gains HP / HP回復
            Beep(880, 10);
            Beep(1200, 10);
        }
    }
    // Clean up used health packs
    // 使用済みの回復アイテムを削除
    hps->ClearDeadPacks();

    // Handle bullet & enemy damage
    // 弾と敵のダメージ処理
    for (auto& pair : bulletEnemyHits) {
        Bullet* b = pair.first;
        Enemy* e = pair.second;

        if (!b->GetIsDead() && !e->GetIsDead()) {
            b->UnderAttack(e->GetHP());          // Bullet takes damage / 弾にダメージ
            e->UnderAttack(b->GetAttackPower()); // Enemy takes damage / 敵にダメージ
            es->AddEliminatedEnemyCount(1);      // Increment eliminated count / 撃破数加算
            ps->AddKillCount(1);                 // Player kill count +1 / プレイヤー撃破数+1
            Beep(1500, 10);
        }
    }

    // Handle player & enemy damage
    // プレイヤーと敵のダメージ処理
    for (auto& e : playerEnemyHits) {
        if (!e->GetIsDead()) {
            ps->UnderAttack(e->GetAttackPower()); // Player takes damage / プレイヤーにダメージ
            e->UnderAttack(e->GetHP());           // Enemy dies / 敵は即死
            es->AddEliminatedEnemyCount(1);       // 撃破数加算
            ps->AddKillCount(1);                  // プレイヤー撃破数+1
            Beep(300, 10);
        }
    }

    // Redundant double-check for player & health pack (safe guard)
    // プレイヤーと回復アイテムの二重チェック（安全策）
    for (auto& hp : hps->GetAllHealthPacks()) {
        if (!hp->GetIsDead() &&
            ps->GetX() == hp->GetX() &&
            ps->GetY() == hp->GetY()) {

            hp->UnderAttack(hp->GetHP());
            ps->AddHP();
            Beep(880, 10);
            Beep(1200, 10);
        }
    }
}
