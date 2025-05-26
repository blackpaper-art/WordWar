#pragma once
#include "../Items/Bullet.h"
#include "../Managers/FieldManager.h"

#include <vector>
#include <memory>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void InitFieldPtr(FieldManager* fm);
	void SpawnBullet(int x, int y, MoveDir dir);
	void DrawAllBullets();
	void Update();
	const std::vector<std::unique_ptr<Bullet>>& GetAllBullet() const;
private:
	std::vector<std::unique_ptr<Bullet>> bullets;
	FieldManager* fieldManager;
};
