#pragma once

#include <vector>
#include <memory>

class HealthPack;

class IHealthPackSystem
{
public:
    virtual const std::vector<std::unique_ptr<HealthPack>>& GetAllHealthPacks() const = 0;
    virtual void SpawnHealthPack() = 0;
    virtual void ClearDeadPacks() = 0;
    virtual ~IHealthPackSystem() {};
};
