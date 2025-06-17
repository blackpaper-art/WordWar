#pragma once
#include "../Characters/Enemies/Enemy.h"
#include "FieldManager.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"

#include <vector>
#include <memory>

class EnemyManager : public IEnemySystem
{
public:
    EnemyManager(IPlayerSystem* p, FieldManager* fm);
    ~EnemyManager();

    void SpawnEnemies(int x, int y, IPlayerSystem* p) override;
    void Update(float deltaTime);

    const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const override;

    void AddEliminatedEnemyCount(int count) override;
    const int GetEliminatedEnemyCount() const override;

private:
    std::vector<std::unique_ptr<Enemy>> enemies;

    IPlayerSystem* playerSystem;
    FieldManager* fieldManager;

    float elapsedTime = 0.0f;
    int eliminatedEnemyCount = 0;
};
