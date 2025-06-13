#include "../Interface/IBulletSystem.h"
#include "../Interface/IEnemySystem.h"
#include "../Characters/Player.h"

#include "CollisionSystem.h"
#include <windows.h> //For Beep()

void CollisionSystem::HandleCollision(Player* p, IBulletSystem* bs, IEnemySystem* es)
{
	//Check collision
	for (const auto& b : bs->GetAllBullets()) {
		if (!b || b->GetIsDead()) continue;

		for (const auto& e : es->GetAllEnemy()) {
			if (!e || e->GetIsDead()) continue;

			if (b->GetX() == e->GetX() && b->GetY() == e->GetY()) {
				e->UnderAttack(b->GetAttackPower());
				b->UnderAttack(b->GetHP());

				es->AddEliminatedEnemyCount(1);

				Beep(1500, 10);//Play sound
				break; //Prevent collison with multi enemies
			}
			else if (p && p->GetX() == e->GetX() && p->GetY() == e->GetY()) {
				p->UnderAttack(e->GetAttackPower());
				e->UnderAttack(e->GetAttackPower());

				es->AddEliminatedEnemyCount(1);

				Beep(300, 10);
				break;
			}
		}
	}
}
