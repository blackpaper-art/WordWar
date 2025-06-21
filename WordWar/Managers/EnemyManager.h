#pragma once
#include "../Characters/Enemies/Enemy.h"
#include "FieldManager.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IPlayerSystem.h"

#include <vector>
#include <memory>

// Manager for all enemies
// ȫ�ƤΔ��������ޥͩ`����`���饹
class EnemyManager : public IEnemySystem
{
public:
    // Constructor / ���󥹥ȥ饯��
    EnemyManager(IPlayerSystem* p, FieldManager* fm);

    // Destructor / �ǥ��ȥ饯��
    ~EnemyManager();                                  

    // Spawn enemy / ��������
    void SpawnEnemies(int x, int y, IPlayerSystem* p) override; 

    // Update enemies / �������
    void Update(float deltaTime);

    // Get all enemies / ȫ�ƤΔ���ȡ��
    const std::vector<std::unique_ptr<Enemy>>& GetAllEnemy() const override; 

    // Add to eliminated count / �����������
    void AddEliminatedEnemyCount(int count) override;      

    // Get eliminated count / ��������ȡ��
    const int GetEliminatedEnemyCount() const override;         

private:
    // Active enemies / �F�ڤΔ��ꥹ��
    std::vector<std::unique_ptr<Enemy>> enemies; 

    // Reference to player system / �ץ쥤��`�����ƥ�ؤβ���
    IPlayerSystem* playerSystem;  

    // Reference to field manager / �ե��`��ɥޥͩ`����`�ؤβ���
    FieldManager* fieldManager;   

    // Time accumulator for spawning / ���ݩ`���äνU�^�r�g
    float elapsedTime = 0.0f;     

    // Total eliminated enemies / ���Ɯg�ߤΔ���
    int eliminatedEnemyCount = 0; 
};
