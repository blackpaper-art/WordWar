#include "ConfigManager.h"
#include <iostream>

// Load configuration from JSON file
// JSON�ե����뤫���O�����i���z��
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
// �ե��`��ɤη���ȡ��
int ConfigManager::GetFieldWidth() const {
    return configData["field"]["width"];
}

// Get field height
// �ե��`��ɤθߤ���ȡ��
int ConfigManager::GetFieldHeight() const {
    return configData["field"]["height"];
}

//------------------------------------------------------------------------------------------------
// PLAYER
//------------------------------------------------------------------------------------------------
// Get player symbol
// �ץ쥤��`�Υ���ܥ��ȡ��
std::string ConfigManager::GetPlayerSymbol() const
{
    return configData["player"]["symbol"].get<std::string>();
}

// Get player's initial HP
// �ץ쥤��`�γ���HP��ȡ��
int ConfigManager::GetPlayerInitialHP() const {
    return configData["player"]["initialHP"];
}

// Get player's initial attack power (AP)
// �ץ쥤��`�γ��ڹ�������ȡ��
int ConfigManager::GetPlayerInitialAP() const
{
    return configData["player"]["initialAP"];
}

// Get player's initial level
// �ץ쥤��`�γ��ڥ�٥��ȡ��
int ConfigManager::GetPlayerInitialPlayerLevel() const
{
    return configData["player"]["initialPlayerLevel"];
}

// Get player's initial bullet level
// �ץ쥤��`�γ��ڏ���٥��ȡ��
int ConfigManager::GetPlayerInitialBulletLevel() const
{
    return configData["player"]["initialBulletLevel"];
}

// Get player's firing interval in ms
// �ץ쥤��`�Ώ��k���g��(ms)��ȡ��
int ConfigManager::GetPlayerInitialFireInterval() const {
    return configData["player"]["initialFireIntervalMs"];
}

// Get player's level up base kills
// �ץ쥤��`�Υ�٥륢�åפλ�����������ȡ��
int ConfigManager::GetPlayerLevelUpBaseKills() const
{
    return configData["player"]["levelUpBaseKills"];
}

// Get player's level up growth factor
// �ץ쥤��`�Υ�٥륢�åפγ��L�S����ȡ��
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
// ���λ������ݩ`���g��(ms)��ȡ��
int ConfigManager::GetEnemyBaseSpawnInterval() const {
    return configData["enemy"]["baseSpawnIntervalMs"];
}

// Get enemy move interval in ms
// �����Ƅ��g��(ms)��ȡ��
float ConfigManager::GetEnemyMoveInterval() const {
    return configData["enemy"]["moveIntervalMs"];
}

//------------------------------------------------------------------------------------------------
// ITEMS (BULLETS & HP Packs)
//------------------------------------------------------------------------------------------------
// Get bullet move interval in ms
// �����Ƅ��g��(ms)��ȡ��
float ConfigManager::GetBulletMoveInterval() const {
    return configData["bullet"]["moveIntervalMs"];
}

// Get health pack symbol
// �؏ͥ����ƥ�Υ���ܥ��ȡ��
std::string ConfigManager::GetHealthPackSymbol() const
{
    return configData["healthPack"]["symbol"].get<std::string>();
}

// Get health pack spawn interval in ms
// �؏ͥ����ƥ�Υ��ݩ`���g��(ms)��ȡ��
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
// ���`���FPS��ȡ��
int ConfigManager::GetGameFPS() const {
    return configData["game"]["fps"];
}

// Get game countdown time in seconds
// ���`��Υ�����ȥ�����r�g(��)��ȡ��
int ConfigManager::GetGameCountDownTime() const
{
    return configData["game"]["countdownSeconds"];
}
