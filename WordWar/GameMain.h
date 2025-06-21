#pragma once
#include "Managers/ConfigManager.h"

// FPS setting from config
// ����ե�������FPS��ȡ��
#define FPS (ConfigManager::GetInstance().GetGameFPS())

// Time gap per frame
// 1�ե�`�ढ����Εr�g�g��
#define TIME_GAP (CLOCKS_PER_SEC / FPS)

// Show the start screen
// �����`�Ȼ�����ʾ
void ShowStartScreen();

// Initialize main game systems
// �ᥤ�󥲩`�����ڻ�
void InitializeMainGame();

// Main game loop
// �ᥤ�󥲩`���`��
void MainGameLoop();

// Shutdown and cleanup
// ���`��K�������Ƭ����
void ShutdownGame();

// Show the game over screen
// ���`�४�`�Щ`������ʾ
void ShowGameOverScreen(int totalKills, int maxLevel);
