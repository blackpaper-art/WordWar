#pragma once
#include "Managers/ConfigManager.h"

// FPS setting from config
// コンフィグからFPSを函誼
#define FPS (ConfigManager::GetInstance().GetGameFPS())

// Time gap per frame
// 1フレ�`ムあたりの�r�g�g侯
#define TIME_GAP (CLOCKS_PER_SEC / FPS)

// Show the start screen
// スタ�`ト鮫中を燕幣
void ShowStartScreen();

// Initialize main game systems
// メインゲ�`ムを兜豚晒
void InitializeMainGame();

// Main game loop
// メインゲ�`ムル�`プ
void MainGameLoop();

// Shutdown and cleanup
// ゲ�`ム�K阻瘁の瘁頭原け
void ShutdownGame();

// Show the game over screen
// ゲ�`ムオ�`バ�`鮫中を燕幣
void ShowGameOverScreen(int totalKills, int maxLevel);
