#include "GameMain.h"
#include "Player.h"
#include "Bullet.h"
#include "Managers/BulletManager.h"

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


Player* player = nullptr;
Bullet* bullet = nullptr;
BulletManager* bulletManager = new BulletManager;

#define FIELD_WIDTH (16*3)
#define FIELD_HEIGHT (9*3)

#define FPS (1)
#define TIME_GAP (CLOCKS_PER_SEC / FPS)
//#define PLAYER_BULLET '.'

#define X_WALL 'X'
#define Y_WALL 'Y'
#define FIELD_NULL ' '

//Safe field info;
int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

void DrawField() {
	//Clean previous field
	system("cls");
	//Draw Field Top Wall
	for (int x = 0; x < FIELD_WIDTH+2; x++)
	{
		putchar(X_WALL);
	}
	printf("\n");

	//Draw both Side Walls and main field
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		putchar(Y_WALL);
		//Draw main field like player enemy etc.
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			char ch = FIELD_NULL;

			if (y == player->GetY() && x == player->GetX())
				ch = player->GetSymbol();

			for (Bullet* b : bulletManager->GetAllBullet()) {
				if (b && y == b->GetY() && x == b->GetX()) {
					ch = b->GetSymbol();
					break; // 一格只显示一个对象
				}
			}

			putchar(ch);
		}
		putchar(Y_WALL);
		printf("\n");
	}

	//Draw Field Down Walls
	for (int x = 0; x < FIELD_WIDTH + 2; x++)
	{
		putchar(X_WALL);
	}
	printf("\n");

	//ShowInfo
	printf("HP: %d", player->ShowPlayerInfo());
}


void MainGameLoop() {
	clock_t lastTime = clock();
	while (true)
	{
		clock_t currentTime = clock();

		if (currentTime >= lastTime + TIME_GAP)
		{
			lastTime = currentTime;
			bulletManager->Update();
			bulletManager->DrawAllBullets();
			DrawField();
		}

		if (_kbhit()) {
			char playerInput = _getch();
			player->Update(playerInput);
			DrawField();
		}
	}
}

int main() {
	//Initialize
	player = new Player(FIELD_WIDTH / 2, FIELD_HEIGHT / 2, bulletManager);
	MainGameLoop();
	delete player;
	return 0;
}