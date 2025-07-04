#include "ConfigManager.h"
#include <iostream>

// Load configuration from JSON file
// JSONファイルから�O協を�iみ�zむ
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
// フィ�`ルドの嫌を函誼
int ConfigManager::GetFieldWidth() const {
    return configData["field"]["width"];
}

// Get field height
// フィ�`ルドの互さを函誼
int ConfigManager::GetFieldHeight() const {
    return configData["field"]["height"];
}

//------------------------------------------------------------------------------------------------
// PLAYER
//------------------------------------------------------------------------------------------------
// Get player symbol
// プレイヤ�`のシンボルを函誼
std::string ConfigManager::GetPlayerSymbol() const
{
    return configData["player"]["symbol"].get<std::string>();
}

// Get player's initial HP
// プレイヤ�`の兜豚HPを函誼
int ConfigManager::GetPlayerInitialHP() const {
    return configData["player"]["initialHP"];
}

// Get player's initial attack power (AP)
// プレイヤ�`の兜豚好�珍Δ鯣ゝ�
int ConfigManager::GetPlayerInitialAP() const
{
    return configData["player"]["initialAP"];
}

// Get player's initial level
// プレイヤ�`の兜豚レベルを函誼
int ConfigManager::GetPlayerInitialPlayerLevel() const
{
    return configData["player"]["initialPlayerLevel"];
}

// Get player's initial bullet level
// プレイヤ�`の兜豚�･譽戰襪鯣ゝ�
int ConfigManager::GetPlayerInitialBulletLevel() const
{
    return configData["player"]["initialBulletLevel"];
}

// Get player's firing interval in ms
// プレイヤ�`の�ｰk符�g侯(ms)を函誼
int ConfigManager::GetPlayerInitialFireInterval() const {
    return configData["player"]["initialFireIntervalMs"];
}

// Get player's level up base kills
// プレイヤ�`のレベルアップの児云�墜栃�を函誼
int ConfigManager::GetPlayerLevelUpBaseKills() const
{
    return configData["player"]["levelUpBaseKills"];
}

// Get player's level up growth factor
// プレイヤ�`のレベルアップの撹�L�S方を函誼
float ConfigManager::GetPlayerLevelUpGrowthFactor() const
{
    return configData["player"]["levelUpGrowthFactor"];
}

// Get player's minimum firing interval in ms
// プレイヤ�`の恷弌�ｰk符�g侯(ms)を函誼
int ConfigManager::GetPlayerMinFireInterval() const
{
    return configData["player"]["initialFireIntervalMs"];
}

// Get player's firing interval scale
// プレイヤ�`の�ｰk符�g侯スケ�`ルを函誼
int ConfigManager::GetPlayerFireIntervalScale() const
{
    return configData["player"]["fireIntervalScale"];
}

// Get bullet upgrade base player level
// �･▲奪廛哀讒`ドの児云プレイヤ�`レベルを函誼
int ConfigManager::GetPlayerBulletUpBaseLevel() const
{
    return configData["player"]["bulletUpBaseLevel"];;
}

//------------------------------------------------------------------------------------------------
// ENEMY
//------------------------------------------------------------------------------------------------
// Get enemy symbol
// �海離轡鵐椒襪鯣ゝ�
std::string ConfigManager::GetEnemySymbol() const
{
    return configData["enemy"]["symbol"].get<std::string>();
}

// Get enemy's initial HP
// �海粒�豚HPを函誼
int ConfigManager::GetEnemyInitialHP() const {
    return configData["enemy"]["initialHP"];
}

// Get enemy's initial attack power (AP)
// �海粒�豚好�珍Δ鯣ゝ�
int ConfigManager::GetEnemyInitialAP() const
{
    return configData["enemy"]["initialAP"];
}

// Get enemy base spawn interval in ms
// �海了�云スポ�`ン�g侯(ms)を函誼
int ConfigManager::GetEnemyBaseSpawnInterval() const {
    return configData["enemy"]["baseSpawnIntervalMs"];
}

// Get enemy move interval in ms
// �海厘��嚔g侯(ms)を函誼
float ConfigManager::GetEnemyMoveInterval() const {
    return configData["enemy"]["moveIntervalMs"];
}

//------------------------------------------------------------------------------------------------
// ITEMS (BULLETS & HP Packs)
//------------------------------------------------------------------------------------------------
// Get bullet symbol
// �､離轡鵐椒襪鯣ゝ�
std::string ConfigManager::GetBulletSymbol() const
{
    return configData["bullet"]["symbol"].get<std::string>();
}

// Get bullet initial HP
// �､粒�豚HPを函誼
int ConfigManager::GetBulletInitialHP() const
{
    return configData["bullet"]["initialHP"];
}

// Get bullet initial attack power (AP)
// �､粒�豚好�珍Δ鯣ゝ�
int ConfigManager::GetBulletInitialAP() const
{
    return configData["bullet"]["initialAP"];
}

// Get bullet move interval in ms
// �､厘��嚔g侯(ms)を函誼
float ConfigManager::GetBulletMoveInterval() const {
    return configData["bullet"]["moveIntervalMs"];
}

// Get health pack symbol
// 指甡▲ぅ謄爐離轡鵐椒襪鯣ゝ�
std::string ConfigManager::GetHealthPackSymbol() const
{
    return configData["healthPack"]["symbol"].get<std::string>();
}

// Get health pack spawn interval in ms
// 指甡▲ぅ謄爐離好櫞`ン�g侯(ms)を函誼
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
// ゲ�`ムのFPSを函誼
int ConfigManager::GetGameFPS() const {
    return configData["game"]["fps"];
}

// Get game countdown time in seconds
// ゲ�`ムのカウントダウン�r�g(昼)を函誼
int ConfigManager::GetGameCountDownTime() const
{
    return configData["game"]["countdownSeconds"];
}
