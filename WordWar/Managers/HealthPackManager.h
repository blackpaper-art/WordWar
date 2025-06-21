#pragma once

#include "../Items/HealthPack.h"
#include "../Managers/TimerManager.h"
#include "../Interface/IHealthPackSystem.h"

#include <vector>
#include <memory>

// Manager for spawning and managing health packs
// �؏ͥ����ƥ�����ɤȹ�����Ф��ޥͩ`����`���饹
class HealthPackManager : public IHealthPackSystem
{
public:
    HealthPackManager(TimerManager* tm); // Constructor / ���󥹥ȥ饯��
    ~HealthPackManager();                // Destructor / �ǥ��ȥ饯��

    void SpawnHealthPack() override;     // Spawn a health pack / �؏ͥ����ƥ������
    void ClearDeadPacks() override;      // Remove dead health packs / ʹ�Üg�ߥ����ƥ������
    const std::vector<std::unique_ptr<HealthPack>>& GetAllHealthPacks() const override; // Get all packs / ȫ�����ƥ�ȡ��

    void Shutdown() {
        // Stop the spawn timer safely
        // ���ݩ`�󥿥��ީ`��ȫ��ֹͣ
        if (spawnTimer) {
            spawnTimer->Stop();
            spawnTimer.reset();
        }
    }

private:
    std::vector<std::unique_ptr<HealthPack>> healthPacks; // Active health packs / �F�ڤλ؏ͥ����ƥ�
    std::shared_ptr<TimerHandle> spawnTimer;              // Timer handle for spawning / ���ݩ`�󥿥��ީ`

    TimerManager* timerManager;                           // Timer manager reference / �����ީ`�ޥͩ`����`
};
