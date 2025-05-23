#include "BulletManager.h"
#include "FieldManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

FieldManager fieldManager;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::SpawnBullet(int x, int y, MoveDir dir)
{
	bullets.push_back(new Bullet(x, y, dir));
}

void BulletManager::DrawAllBullets()
{
	for (Bullet* b : bullets)
	{
		int x = b->GetX();
		int y = b->GetY();
		if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
			fieldManager.SetField(x, y, b->GetSymbol());
		}
	}
}

void BulletManager::Update() 
{
	for (Bullet* b : bullets)
	{
		if (b) b->Update();
	}
}

int BulletManager::GetAllBullet()
{
	int bulletsNum = 0;
	for (Bullet* b : bullets)
	{
		bulletsNum++;
	}
	return bulletsNum;
}
