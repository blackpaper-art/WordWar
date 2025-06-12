#include "../Managers/BulletManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}


void BulletManager::SpawnBullet(int x, int y, MoveDir dir)
{
	bullets.push_back(std::make_unique<Bullet>(x, y, dir));
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
			it = bullets.erase(it);
		}
		else { ++it; }
	}
}

const std::vector<std::unique_ptr<Bullet>>& BulletManager::GetAllBullets() const
{
	return bullets;
}

int BulletManager::GetBulletCount() const
{
	return static_cast<int>(bullets.size());;
}