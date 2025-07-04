#pragma once
#include "../Libs/json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;

class ConfigManager
{
public:
	// Get singleton instance
	// シングルトンインスタンス函誼
	static ConfigManager& GetInstance() {
		static ConfigManager instance;
		return instance;
	}

	// Prohibit copy and assignment
	// コピ�`と旗秘を鋤峭
	ConfigManager(const ConfigManager&) = delete;
	void operator=(const ConfigManager&) = delete;

	// Load config file
	// �O協ファイルを�iみ�zむ
	void LoadConfig(const std::string& configFilePath);

	// Get Field info
	// フィ�`ルド秤�麋ゝ�
	int GetFieldWidth() const;
	int GetFieldHeight() const;

	// Get Player info
	// プレイヤ�`秤�麋ゝ�
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
	// �廓��麋ゝ�
	std::string GetEnemySymbol() const;

	int GetEnemyInitialHP() const;
	int GetEnemyInitialAP() const;

	int GetEnemyBaseSpawnInterval() const;
	float GetEnemyMoveInterval() const;

	// Get bullet info
	// �ﾇ��麋ゝ�
	std::string GetBulletSymbol() const;

	int GetBulletInitialHP() const;
	int GetBulletInitialAP() const;

	float GetBulletMoveInterval() const;

	// Get health pack info
	// 指甡▲ぅ謄倏��麋ゝ�
	std::string GetHealthPackSymbol() const;
	int GetHealthPackSpawnInterval() const;
	int GetHealthPackHealAmount() const;

	// Get game settings
	// ゲ�`ム�O協函誼
	int GetGameFPS() const;
	int GetGameCountDownTime() const;

private:
	ConfigManager() = default;

	// Save config data
	// Config秤�鷄４�
	json configData;
};