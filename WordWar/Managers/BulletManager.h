#pragma once
#include "../Bullet.h"
#include <vector>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void SpawnBullet(int x, int y, MoveDir dir);
	void DrawAllBullets();
	void Update();
	int GetAllBullet();
private:
	std::vector<Bullet*> bullets;
};
