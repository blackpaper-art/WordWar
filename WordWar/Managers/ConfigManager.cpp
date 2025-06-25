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

//------------------------------------------------------------------------------------------------
// FIELD
//------------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------
// PLAYER
//------------------------------------------------------------------------------------------------
// Get player symbol
// プレイヤーのシンボルを取得
std::string ConfigManager::GetPlayerSymbol() const
{
    return configData["player"]["symbol"].get<std::string>();
}

// Get player's initial HP
// プレイヤーの初期HPを取得
int ConfigManager::GetPlayerInitialHP() const {
    return configData["player"]["initialHP"];
}

// Get player's initial attack power (AP)
// プレイヤーの初期攻撃力を取得
int ConfigManager::GetPlayerInitialAP() const
{
    return configData["player"]["initialAP"];
}

// Get player's initial level
// プレイヤーの初期レベルを取得
int ConfigManager::GetPlayerInitialPlayerLevel() const
{
    return configData["player"]["initialPlayerLevel"];
}

// Get player's initial bullet level
// プレイヤーの初期弾レベルを取得
int ConfigManager::GetPlayerInitialBulletLevel() const
{
    return configData["player"]["initialBulletLevel"];
}

// Get player's firing interval in ms
// プレイヤーの弾発射間隔(ms)を取得
int ConfigManager::GetPlayerInitialFireInterval() const {
    return configData["player"]["initialFireIntervalMs"];
}

// Get player's level up base kills
// プレイヤーのレベルアップの基本撃破数を取得
int ConfigManager::GetPlayerLevelUpBaseKills() const
{
    return configData["player"]["levelUpBaseKills"];
}

// Get player's level up growth factor
// プレイヤーのレベルアップの成長係数を取得
float ConfigManager::GetPlayerLevelUpGrowthFactor() const
{
    return configData["player"]["levelUpGrowthFactor"];
}

int ConfigManager::GetPlayerBulletUpBaseLevel() const
{
    return configData["player"]["bulletUpBaseLevel"];;
}

//------------------------------------------------------------------------------------------------
// ENEMY
//------------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------
// ITEMS (BULLETS & HP Packs)
//------------------------------------------------------------------------------------------------
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

int ConfigManager::GetHealthPackHealAmount() const
{
    return configData["healthPack"]["healAmount"];
}

//------------------------------------------------------------------------------------------------
// GAME SETTINGS
// ------------------------------------------------------------------------------------------------
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
