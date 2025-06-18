#pragma once
#include "../Items/Bullet.h"
#include "../Interface/IBulletSystem.h"

#include <vector>
#include <memory>

class BulletManager : public IBulletSystem
{
public:
	BulletManager();
	~BulletManager();

	void SpawnBullet(int x, int y, MoveDir dir, int bulletLevel) override;
	void Update(float deltaTime);
	const std::vector<std::unique_ptr<Bullet>>& GetAllBullets() const override;
	int GetBulletCount() const override;

private:
	std::vector<std::unique_ptr<Bullet>> bullets;
};
