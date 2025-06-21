#pragma once
#include "Managers/ConfigManager.h"

// FPS setting from config
// コンフィグからFPSを取得
#define FPS (ConfigManager::GetInstance().GetGameFPS())

// Time gap per frame
// 1フレームあたりの時間間隔
#define TIME_GAP (CLOCKS_PER_SEC / FPS)

// Show the start screen
// スタート画面を表示
void ShowStartScreen();

// Initialize main game systems
// メインゲームを初期化
void InitializeMainGame();

// Main game loop
// メインゲームループ
void MainGameLoop();

// Shutdown and cleanup
// ゲーム終了後の後片付け
void ShutdownGame();

// Show the game over screen
// ゲームオーバー画面を表示
void ShowGameOverScreen(int totalKills, int maxLevel);
