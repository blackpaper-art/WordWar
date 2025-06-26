#pragma once
#include "../Libs/json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;

class ConfigManager
{
public:
	// Get singleton instance
	// ���󥰥�ȥ󥤥󥹥���ȡ��
	static ConfigManager& GetInstance() {
		static ConfigManager instance;
		return instance;
	}

	// Prohibit copy and assignment
	// ���ԩ`�ȴ�����ֹ
	ConfigManager(const ConfigManager&) = delete;
	void operator=(const ConfigManager&) = delete;

	// Load config file
	// �O���ե�������i���z��
	void LoadConfig(const std::string& configFilePath);

	// Get Field info
	// �ե��`������ȡ��
	int GetFieldWidth() const;
	int GetFieldHeight() const;

	// Get Player info
	// �ץ쥤��`���ȡ��
	std::string GetPlayerSymbol() const;

	int GetPlayerInitialHP() const;
	int GetPlayerInitialAP() const;

	int GetPlayerInitialPlayerLevel() const;
	int GetPlayerInitialBulletLevel() const;
	int GetPlayerInitialFireInterval() const;
	int GetPlayerMinFireInterval() const;
	int GetPlayerFireIntervalScale() const;

	int GetPlayerLevelUpBaseKills() const;
	float GetPlayerLevelUpGrowthFactor() const;

	int GetPlayerBulletUpBaseLevel() const;

	// Get enemy info
	// �����ȡ��
	std::string GetEnemySymbol() const;

	int GetEnemyInitialHP() const;
	int GetEnemyInitialAP() const;

	int GetEnemyBaseSpawnInterval() const;
	float GetEnemyMoveInterval() const;

	// Get bullet info
	// �����ȡ��
	std::string GetBulletSymbol() const;

	int GetBulletInitialHP() const;
	int GetBulletInitialAP() const;

	float GetBulletMoveInterval() const;

	// Get health pack info
	// �؏ͥ����ƥ����ȡ��
	std::string GetHealthPackSymbol() const;
	int GetHealthPackSpawnInterval() const;
	int GetHealthPackHealAmount() const;

	// Get game settings
	// ���`���O��ȡ��
	int GetGameFPS() const;
	int GetGameCountDownTime() const;

private:
	ConfigManager() = default;

	// Save config data
	// Config��󱣴�
	json configData;
};