#pragma once

#include "../Items/HealthPack.h"
#include "../Managers/TimerManager.h"
#include "../Interface/IHealthPackSystem.h"

#include <vector>
#include <memory>

class HealthPackManager : public IHealthPackSystem
{
public:
    HealthPackManager(TimerManager* tm);
    ~HealthPackManager();

    void SpawnHealthPack() override;
    void ClearDeadPacks() override;
    const std::vector<std::unique_ptr<HealthPack>>& GetAllHealthPacks() const override;

    void Shutdown() {
        if (spawnTimer) {
            spawnTimer->Stop();
            spawnTimer.reset();
        }
    }
private:
    std::vector<std::unique_ptr<HealthPack>> healthPacks;
    std::shared_ptr<TimerHandle> spawnTimer;

    TimerManager* timerManager;
};
