#pragma once
#include "../Libs/json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;

class ConfigManager
{
public:
	// Get singleton instance
	// シングルトンインスタンス取得
	static ConfigManager& GetInstance() {
		static ConfigManager instance;
		return instance;
	}

	//Prohibit copy and assignment
	ConfigManager(const ConfigManager&) = delete;
	void operator=(const ConfigManager&) = delete;

	// Load file
	void LoadConfig(const std::string& configFilePath);

	// Get Field info
	int GetFieldWidth() const;
	int GetFieldHeight() const;

	// Get Player info
	std::string GetPlayerSymbol() const;
	int GetPlayerInitialAP() const;
	int GetPlayerInitialHP() const;
	int GetPlayerFireInterval() const;

	int GetEnemyBaseSpawnInterval() const;
	float GetEnemyMoveInterval() const;

	float GetBulletMoveInterval() const;

	// Get HealthPack info
	std::string GetHealthPackSymbol() const;
	int GetHealthPackSpawnInterval() const;

	// Get Game info
	int GetGameFPS() const;
	int GetGameCountDownTime() const;

private:
	ConfigManager() = default;
	// Save config data
	// Config情報保存
	json configData;
};