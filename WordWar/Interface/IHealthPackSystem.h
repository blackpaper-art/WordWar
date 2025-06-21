#pragma once

#include <vector>
#include <memory>

class HealthPack;

// Interface for health pack system
// �؏ͥ����ƥॷ���ƥ��å��󥿩`�ե��`��
class IHealthPackSystem
{
public:
    // Get all active health packs
    // �F�ڤλ؏ͥ����ƥ��ȡ��
    virtual const std::vector<std::unique_ptr<HealthPack>>& GetAllHealthPacks() const = 0;

    // Spawn a new health pack
    // �¤����؏ͥ����ƥ������
    virtual void SpawnHealthPack() = 0;

    // Remove dead or used health packs
    // ʹ���Фä��؏ͥ����ƥ������
    virtual void ClearDeadPacks() = 0;

    virtual ~IHealthPackSystem() {};
};
