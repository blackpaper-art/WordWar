#include "ConfigManager.h"
#include <iostream>

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

std::string ConfigManager::GetPlayerSymbol() const
{
	return configData["player"]["symbol"].get<std::string>();
}

int ConfigManager::GetPlayerInitialAP() const
{
	return configData["player"]["initialAP"];
}

int ConfigManager::GetFieldWidth() const {
	return configData["field"]["width"];
}

int ConfigManager::GetFieldHeight() const {
	return configData["field"]["height"];
}

int ConfigManager::GetPlayerInitialHP() const {
	return configData["player"]["initialHP"];
}

int ConfigManager::GetPlayerFireInterval() const {
	return configData["player"]["fireIntervalMs"];
}

int ConfigManager::GetEnemyBaseSpawnInterval() const {
	return configData["enemy"]["baseSpawnIntervalMs"];
}

float ConfigManager::GetEnemyMoveInterval() const {
	return configData["enemy"]["moveIntervalMs"];
}

float ConfigManager::GetBulletMoveInterval() const {
	return configData["bullet"]["moveIntervalMs"];
}

std::string ConfigManager::GetHealthPackSymbol() const
{
	return configData["healthPack"]["symbol"].get<std::string>();
}

int ConfigManager::GetHealthPackSpawnInterval() const
{
	return configData["healthPack"]["spawnIntervalMs"];
}

int ConfigManager::GetGameFPS() const {
	return configData["game"]["fps"];
}

int ConfigManager::GetGameCountDownTime() const
{
	return configData["game"]["countdownSeconds"];
}
