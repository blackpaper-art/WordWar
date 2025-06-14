#pragma once
#define FPS (30)
#define TIME_GAP (CLOCKS_PER_SEC / FPS)

void ShowStartScreen();

void InitializeMainGame();
void MainGameLoop();
void ShutdownGame();

void ShowGameOverScreen(int totalKills, int maxLevel);