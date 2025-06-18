#include "../Interface/IBulletSystem.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"
#include "../Interface/IHealthPackSystem.h"

#include "../Items/HealthPack.h"

#include "CollisionSystem.h"
#include <windows.h> //For Beep()

void CollisionSystem::HandleCollision(IPlayerSystem* ps, IBulletSystem* bs, IEnemySystem* es, IHealthPackSystem* hps)
{
    //Check collision
    std::vector<std::pair<Bullet*, Enemy*>> bulletEnemyHits;
    std::vector<Enemy*> playerEnemyHits;
    std::vector<HealthPack*> playerHealthPackHit;

    //Bullet & Enemy
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

    //Player & Enemy
    for (const auto& e : es->GetAllEnemy()) {
        if (!e || e->GetIsDead()) continue;

        if (ps->GetX() == e->GetX() && ps->GetY() == e->GetY()) {
            playerEnemyHits.push_back(e.get());
            break;
        }
    }

    //Player & HealthPack
    for (const auto& hp : hps->GetAllHealthPacks()) {
        if (!hp->GetIsDead() && ps->GetX() == hp->GetX() && ps->GetY() == hp->GetY()) {
            hp->UnderAttack(hp->GetHP());
            ps->AddHP();
            Beep(880, 10);
            Beep(1200, 10);
        }
    }
    hps->ClearDeadPacks();

    //Handle bullet and enemy
    for (auto& pair : bulletEnemyHits) {
        Bullet* b = pair.first;
        Enemy* e = pair.second;

        if (!b->GetIsDead() && !e->GetIsDead()) {
            b->UnderAttack(e->GetHP());
            e->UnderAttack(b->GetAttackPower());
            es->AddEliminatedEnemyCount(1);
            ps->AddKillCount(1);
            Beep(1500, 10);
        }
    }

    //Handle player and enemy
    for (auto& e : playerEnemyHits) {
        if (!e->GetIsDead()) {
            ps->UnderAttack(e->GetAttackPower());
            e->UnderAttack(e->GetHP());
            es->AddEliminatedEnemyCount(1);
            ps->AddKillCount(1);
            Beep(300, 10);
        }
    }

    //Handle player and health pack
    for (auto& hp : hps->GetAllHealthPacks()) {
        if (!hp->GetIsDead() &&
            ps->GetX() == hp->GetX() &&
            ps->GetY() == hp->GetY()) {

            hp->UnderAttack(hp->GetHP()); // ÉèÖÃËÀµô
            ps->AddHP();
            Beep(880, 10);
            Beep(1200, 10);
        }
    }
}
