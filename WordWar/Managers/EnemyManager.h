#pragma once
#include "../Characters/Enemies/Enemy.h"
#include "FieldManager.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"

#include <vector>
#include <memory>

// Manager for all enemies
// 全ての敵を管理するマネージャークラス
class EnemyManager : public IEnemySystem
{
public:
    // Constructor / コンストラクタ
    EnemyManager(IPlayerSystem* p, FieldManager* fm);

    // Destructor / デストラクタ
    ~EnemyManager();                                  

    // Spawn enemy / 敵を生成
    void SpawnEnemies(int x, int y, IPlayerSystem* p) override; 

    // Update enemies / 敵を更新
    void Update(float deltaTime);

    // Get all enemies / 全ての敵を取得
    const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const override; 

    // Add to eliminated count / 撃破数を加算
    void AddEliminatedEnemyCount(int count) override;      

    // Get eliminated count / 撃破数を取得
    const int GetEliminatedEnemyCount() const override;         

private:
    // Active enemies / 現在の敵リスト
    std::vector<std::unique_ptr<Enemy>> enemies; 

    // Reference to player system / プレイヤーシステムへの参照
    IPlayerSystem* playerSystem;  

    // Reference to field manager / フィールドマネージャーへの参照
    FieldManager* fieldManager;   

    // Time accumulator for spawning / スポーン用の経過時間
    float elapsedTime = 0.0f;     

    // Total eliminated enemies / 撃破済みの敵数
    int eliminatedEnemyCount = 0; 
};
