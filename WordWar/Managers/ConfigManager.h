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

	// Prohibit copy and assignment
	// コピーと代入を禁止
	ConfigManager(const ConfigManager&) = delete;
	void operator=(const ConfigManager&) = delete;

	// Load config file
	// 設定ファイルを読み込む
	void LoadConfig(const std::string& configFilePath);

	// Get Field info
	// フィールド情報取得
	int GetFieldWidth() const;
	int GetFieldHeight() const;

	// Get Player info
	// プレイヤー情報取得
	std::string GetPlayerSymbol() const;
	int GetPlayerInitialAP() const;
	int GetPlayerInitialHP() const;
	int GetPlayerFireInterval() const;

	// Get enemy info
	// 敵情報取得
	int GetEnemyBaseSpawnInterval() const;
	float GetEnemyMoveInterval() const;

	// Get bullet info
	// 弾情報取得
	float GetBulletMoveInterval() const;

	// Get health pack info
	// 回復アイテム情報取得
	std::string GetHealthPackSymbol() const;
	int GetHealthPackSpawnInterval() const;

	// Get game settings
	// ゲーム設定取得
	int GetGameFPS() const;
	int GetGameCountDownTime() const;

private:
	ConfigManager() = default;

	// Save config data
	// Config情報保存
	json configData;
};