#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "GameMain.h"
#include "Player.h"
#include "Bullet.h"

Player* player = nullptr;
Bullet* bullet = nullptr;

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
			else if (y == bullet->GetY() && x == bullet->GetX())
				ch = bullet->GetSymbol();

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
	printf("HP: %d", player->ShowPlayerInfo());
	//putchar();
	
}


void MainGameLoop() {
	clock_t lastTime = clock();
	while (true)
	{
		clock_t currentTime = clock();

		if (currentTime >= lastTime + TIME_GAP)
		{
			lastTime = currentTime;
			bullet->Update();
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
	player = new Player(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);
	bullet = new Bullet(player->GetX(), player->GetY());
	
	

	MainGameLoop();
	delete player;
	return 0;
}