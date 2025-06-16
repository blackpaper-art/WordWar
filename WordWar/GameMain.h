#pragma once
#include "Managers/ConfigManager.h"
#define FPS (ConfigManager::GetInstance().GetGameFPS())
#define TIME_GAP (CLOCKS_PER_SEC / FPS)

void ShowStartScreen();

void InitializeMainGame();
void MainGameLoop();
void ShutdownGame();

void ShowGameOverScreen(int totalKills, int maxLevel);