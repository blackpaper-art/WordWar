#include "ConfigManager.h"
#include <iostream>

// Load configuration from JSON file
// JSONファイルから設定を読み込む
void ConfigManager::LoadConfig(const std::string& configFilePath)
{
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open())
    {
        std::cerr << "Error: Can not open the config file: " << configFilePath << std::endl;
        exit(1);
    }

    try
    {
        configData = json::parse(configFile);
    }
    catch (json::parse_error& e)
    {
        std::cerr << "Error: JSON parse error in " << configFilePath << ": " << e.what() << std::endl;
        exit(1);
    }
}

// Get player symbol
// プレイヤーのシンボルを取得
std::string ConfigManager::GetPlayerSymbol() const
{
    return configData["player"]["symbol"].get<std::string>();
}

// Get player's initial attack power (AP)
// プレイヤーの初期攻撃力を取得
int ConfigManager::GetPlayerInitialAP() const
{
    return configData["player"]["initialAP"];
}

// Get field width
// フィールドの幅を取得
int ConfigManager::GetFieldWidth() const {
    return configData["field"]["width"];
}

// Get field height
// フィールドの高さを取得
int ConfigManager::GetFieldHeight() const {
    return configData["field"]["height"];
}

// Get player's initial HP
// プレイヤーの初期HPを取得
int ConfigManager::GetPlayerInitialHP() const {
    return configData["player"]["initialHP"];
}

// Get player's firing interval in ms
// プレイヤーの弾発射間隔(ms)を取得
int ConfigManager::GetPlayerFireInterval() const {
    return configData["player"]["fireIntervalMs"];
}

// Get enemy base spawn interval in ms
// 敵の基本スポーン間隔(ms)を取得
int ConfigManager::GetEnemyBaseSpawnInterval() const {
    return configData["enemy"]["baseSpawnIntervalMs"];
}

// Get enemy move interval in ms
// 敵の移動間隔(ms)を取得
float ConfigManager::GetEnemyMoveInterval() const {
    return configData["enemy"]["moveIntervalMs"];
}

// Get bullet move interval in ms
// 弾の移動間隔(ms)を取得
float ConfigManager::GetBulletMoveInterval() const {
    return configData["bullet"]["moveIntervalMs"];
}

// Get health pack symbol
// 回復アイテムのシンボルを取得
std::string ConfigManager::GetHealthPackSymbol() const
{
    return configData["healthPack"]["symbol"].get<std::string>();
}

// Get health pack spawn interval in ms
// 回復アイテムのスポーン間隔(ms)を取得
int ConfigManager::GetHealthPackSpawnInterval() const
{
    return configData["healthPack"]["spawnIntervalMs"];
}

// Get game FPS
// ゲームのFPSを取得
int ConfigManager::GetGameFPS() const {
    return configData["game"]["fps"];
}

// Get game countdown time in seconds
// ゲームのカウントダウン時間(秒)を取得
int ConfigManager::GetGameCountDownTime() const
{
    return configData["game"]["countdownSeconds"];
}
