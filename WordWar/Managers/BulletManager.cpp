#include "../Managers/BulletManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::InitFieldPtr(FieldManager* fm)
{
	fieldManager = fm;
}

void BulletManager::SpawnBullet(int x, int y, MoveDir dir)
{
	bullets.push_back(std::make_unique<Bullet>(x, y, dir));
}

void BulletManager::DrawAllBullets()
{
	for (const auto& b : bullets)
	{
		int x = b->GetX();
		int y = b->GetY();
		if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
			fieldManager->SetField(x, y, b->GetSymbol());
		}
	}
}

void BulletManager::Update(float deltaTime)
{
	auto it = bullets.begin();
	while (it != bullets.end())
	{
		//if this it is a nullptr then delete it
		if (it->get() == nullptr) {
			it = bullets.erase(it);
			continue;
		}

		(*it)->Update(deltaTime);
		if ((*it)->GetIsDead() || (*it)->GetIsOutOfField())
		{
			if ((*it)->GetIsDead())
			{
				eliminatedEnemyCount++;
			}
			it = bullets.erase(it);
		}
		else { ++it; }
	}
}

const std::vector<std::unique_ptr<Bullet>>& BulletManager::GetAllBullet() const
{
	return bullets;
}

const int BulletManager::GetEliminatedEnemyCount() const
{
	return eliminatedEnemyCount;
}
