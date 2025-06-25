#include "HealthPackManager.h"
#include "../Managers/ConfigManager.h"

// Constructor: initialize health pack spawn timer
// ���󥹥ȥ饯�����؏ͥ����ƥ�Υ��ݩ`�󥿥��ީ`����ڻ�
HealthPackManager::HealthPackManager(TimerManager* tm)
    : timerManager(tm)
{
    // Spawn health pack repeatedly using timer
    // �����ީ`�Ƕ��ڵĤ˻؏ͥ����ƥ������
    spawnTimer = timerManager->SetTimer(
        ConfigManager::GetInstance().GetHealthPackSpawnInterval(),
        [this] { SpawnHealthPack(); },
        true
    );
}

// Destructor
// �ǥ��ȥ饯��
HealthPackManager::~HealthPackManager() {}

// Spawn a new health pack at random position
// �������λ�ä��¤����؏ͥ����ƥ������
void HealthPackManager::SpawnHealthPack()
{
    int x = rand() % ConfigManager::GetInstance().GetFieldWidth();
    int y = rand() % ConfigManager::GetInstance().GetFieldHeight();
    healthPacks.push_back(std::make_unique<HealthPack>(x, y));
}

// Remove dead health packs
// ʹ�Üg�ߤλ؏ͥ����ƥ������
void HealthPackManager::ClearDeadPacks()
{
    healthPacks.erase(
        std::remove_if(healthPacks.begin(), healthPacks.end(),
            [](const std::unique_ptr<HealthPack>& hp) {
                return hp->GetIsDead();
            }),
        healthPacks.end()
    );
}

// Get all active health packs
// �F�ڤλ؏ͥ����ƥ��ȡ��
const std::vector<std::unique_ptr<HealthPack>>& HealthPackManager::GetAllHealthPacks() const
{
    return healthPacks;
}
