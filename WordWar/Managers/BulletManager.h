#pragma once
#include "../Items/Bullet.h"
#include <vector>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void SpawnBullet(int x, int y, MoveDir dir);
	void DrawAllBullets();
	void Update();
	const std::vector<Bullet*>& GetAllBullet() const;
private:
	std::vector<Bullet*> bullets;
};
