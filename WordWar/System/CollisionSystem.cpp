#include "../Interface/IBulletSystem.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"

#include "CollisionSystem.h"
#include <windows.h> //For Beep()

void CollisionSystem::HandleCollision(IPlayerSystem* ps, IBulletSystem* bs, IEnemySystem* es)
{
    //Check collision
    std::vector<std::pair<Bullet*, Enemy*>> bulletEnemyHits;
    std::vector<Enemy*> playerEnemyHits;

    for (const auto& b : bs->GetAllBullets()) {
        if (!b || b->GetIsDead()) continue;

        for (const auto& e : es->GetAllEnemy()) {
            if (!e || e->GetIsDead()) continue;

            if (b->GetX() == e->GetX() && b->GetY() == e->GetY()) {
                bulletEnemyHits.push_back({ b.get(), e.get() });
                break;
            }
            else if (ps && ps->GetX() == e->GetX() && ps->GetY() == e->GetY()) {
                playerEnemyHits.push_back(e.get());
                break;
            }
        }
    }

    //Handle bullet and enemy
    for (auto& pair : bulletEnemyHits) {
        Bullet* b = pair.first;
        Enemy* e = pair.second;

        if (!b->GetIsDead() && !e->GetIsDead()) {
            e->UnderAttack(b->GetAttackPower());
            b->UnderAttack(b->GetHP());
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
}
