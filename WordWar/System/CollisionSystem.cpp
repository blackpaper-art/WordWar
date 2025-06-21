#include "../Interface/IBulletSystem.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"
#include "../Interface/IHealthPackSystem.h"

#include "../Items/HealthPack.h"

#include "CollisionSystem.h"
#include <windows.h> // For Beep()

// Handle all collisions between bullets, enemies, player, and health packs
// ���������ץ쥤��`���؏ͥ����ƥ��g��ȫ�Ƥ��nͻ��I��
void CollisionSystem::HandleCollision(
    IPlayerSystem* ps,
    IBulletSystem* bs,
    IEnemySystem* es,
    IHealthPackSystem* hps)
{
    // Prepare hit records
    // �������ж��νY����ӛ�h
    std::vector<std::pair<Bullet*, Enemy*>> bulletEnemyHits;
    std::vector<Enemy*> playerEnemyHits;

    // Bullet & Enemy collision
    // ���Ȕ����nͻ
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
    // �ץ쥤��`�Ȕ����nͻ
    for (const auto& e : es->GetAllEnemy()) {
        if (!e || e->GetIsDead()) continue;

        if (ps->GetX() == e->GetX() && ps->GetY() == e->GetY()) {
            playerEnemyHits.push_back(e.get());
            break;
        }
    }

    // Player & HealthPack collision
    // �ץ쥤��`�Ȼ؏ͥ����ƥ���nͻ
    for (const auto& hp : hps->GetAllHealthPacks()) {
        if (!hp->GetIsDead() && ps->GetX() == hp->GetX() && ps->GetY() == hp->GetY()) {
            hp->UnderAttack(hp->GetHP()); // Mark as used / ʹ�Üg�ߤˤ���
            ps->AddHP();                  // Player gains HP / HP�؏�
            Beep(880, 10);
            Beep(1200, 10);
        }
    }
    // Clean up used health packs
    // ʹ�Üg�ߤλ؏ͥ����ƥ������
    hps->ClearDeadPacks();

    // Handle bullet & enemy damage
    // ���Ȕ��Υ���`���I��
    for (auto& pair : bulletEnemyHits) {
        Bullet* b = pair.first;
        Enemy* e = pair.second;

        if (!b->GetIsDead() && !e->GetIsDead()) {
            b->UnderAttack(e->GetHP());          // Bullet takes damage / ���˥���`��
            e->UnderAttack(b->GetAttackPower()); // Enemy takes damage / ���˥���`��
            es->AddEliminatedEnemyCount(1);      // Increment eliminated count / ����������
            ps->AddKillCount(1);                 // Player kill count +1 / �ץ쥤��`������+1
            Beep(1500, 10);
        }
    }

    // Handle player & enemy damage
    // �ץ쥤��`�Ȕ��Υ���`���I��
    for (auto& e : playerEnemyHits) {
        if (!e->GetIsDead()) {
            ps->UnderAttack(e->GetAttackPower()); // Player takes damage / �ץ쥤��`�˥���`��
            e->UnderAttack(e->GetHP());           // Enemy dies / ���ϼ���
            es->AddEliminatedEnemyCount(1);       // ����������
            ps->AddKillCount(1);                  // �ץ쥤��`������+1
            Beep(300, 10);
        }
    }

    // Redundant double-check for player & health pack (safe guard)
    // �ץ쥤��`�Ȼ؏ͥ����ƥ�ζ��إ����å�����ȫ�ߣ�
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
