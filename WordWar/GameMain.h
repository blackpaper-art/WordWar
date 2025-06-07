#pragma once
#define FPS (1)
#define TIME_GAP (CLOCKS_PER_SEC / FPS)

void InitializeMainGame();
void MainGameLoop();
void ShutdownGame();