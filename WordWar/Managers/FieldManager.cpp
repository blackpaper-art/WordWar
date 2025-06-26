/*---------------------------------------------------------------------------------------------*
 * Description / 説明 :                                                                         *
 *  FieldManager is responsible for managing the game field, including rendering,              *
 *  updating the field state, and delegating collision detection between bullets,              *
 *  enemies, and the player to the CollisionSystem.                                            *
 *                                                                                             *
 *  FieldManager クラスはゲームフィールドの管理を担当します。描画処理、状態の更新、                      *
 *  そして弾丸・敵・プレイヤー間の衝突判定を CollisionSystem に委託します。                            *
 *---------------------------------------------------------------------------------------------*/

#include "FieldManager.h"
#include "TimerManager.h"
#include "ConfigManager.h"

#include "../Items/HealthPack.h"
#include "../Interface/IEnemySystem.h"
#include "../Interface/IBulletSystem.h"
#include "../Interface/IPlayerSystem.h"
#include "../Interface/IHealthPackSystem.h"
#include "../System/CollisionSystem.h"

#include <windows.h>
#include <algorithm>
#include <vector>
#include <memory>

 // Constructor
 // コンストラクタ
FieldManager::FieldManager()
    : countDownTime(ConfigManager::GetInstance().GetGameCountDownTime()),
    fieldWidth(ConfigManager::GetInstance().GetFieldWidth()),
    fieldHeight(ConfigManager::GetInstance().GetFieldHeight()),
    showDebugMessage(false)
{
    // Initialize field buffer
    // フィールドバッファ初期化
    fieldBuffer.resize(fieldHeight, std::vector<char>(fieldWidth, FIELD_NULL));

    if (countDownTimer) {
        countDownTimer->isActive = false;
    }
}

// Destructor
// デストラクタ
FieldManager::~FieldManager() {}

// Initialize managers and setup countdown timer
// 他のマネージャーを初期化し、カウントダウンタイマーを設定
void FieldManager::InitializeManagers(
    IPlayerSystem* ps, IEnemySystem* es, IBulletSystem* bs, IHealthPackSystem* hps, TimerManager* tm)
{
    playerSystem = ps;
    enemySystem = es;
    bulletSystem = bs;
    healthPackSystem = hps;

    if (ConfigManager::GetInstance().GetGameCountDownTime() != 0)
    {
        auto self = shared_from_this();
        countDownTimer = tm->SetTimer(1000, [weakSelf = std::weak_ptr<FieldManager>(self)] {
            if (auto s = weakSelf.lock()) {
                s->CountDownTimer();
            }
            }, true);
    }
}

// Update deltaTime for debug info
// deltaTimeを更新（デバッグ用）
void FieldManager::Update(float deltaTime)
{
    myDeltaTime = deltaTime;
}

// Draw entire game field with buffer and info panel
// バッファを使ってフィールド全体と情報パネルを描画
void FieldManager::DrawField()
{
    // 1. Clear buffer
    // バッファをクリア
    for (int y = 0; y < fieldHeight; y++)
    {
        for (int x = 0; x < fieldWidth; x++)
        {
            fieldBuffer[y][x] = FIELD_NULL;
        }
    }

    // 2. Fill buffer with objects
    // バッファに各オブジェクトを描画
    if (enemySystem) {
        for (const auto& e : enemySystem->GetAllEnemy()) {
            if (e && !e->GetIsDead()) {
                fieldBuffer[e->GetY()][e->GetX()] = e->GetSymbol();
            }
        }
    }

    if (bulletSystem) {
        for (const auto& b : bulletSystem->GetAllBullets()) {
            if (b && !b->GetIsDead()) {
                fieldBuffer[b->GetY()][b->GetX()] = b->GetSymbol();
            }
        }
    }

    if (playerSystem) {
        fieldBuffer[playerSystem->GetY()][playerSystem->GetX()] = playerSystem->GetSymbol();
    }

    if (healthPackSystem) {
        for (const auto& hp : healthPackSystem->GetAllHealthPacks()) {
            if (hp && !hp->GetIsDead()) {
                fieldBuffer[hp->GetY()][hp->GetX()] = hp->GetSymbol();
            }
        }
    }

    // 3. Draw buffer and info
    // バッファを描画して情報を表示
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    SetConsoleCursorPosition(hConsole, coordScreen);

    // Top wall
    for (int x = 0; x < ConfigManager::GetInstance().GetFieldWidth() + 2; x++) {
        putchar(X_WALL);
    }
    printf("\n");

    // Main field + side info
    for (int y = 0; y < fieldHeight; y++) {
        putchar(Y_WALL);
        for (int x = 0; x < fieldWidth; x++) {
            char c = fieldBuffer[y][x];
            if (c == ConfigManager::GetInstance().GetHealthPackSymbol()[0]) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                putchar(c);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else if (c == playerSystem->GetSymbol()) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                putchar(c);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                putchar(c);
            }
        }

        putchar(Y_WALL);

        // Info panel
        if (y == 0 && ConfigManager::GetInstance().GetGameCountDownTime() != 0) {
            printf(" Time Left: %-4d seconds", countDownTime);
        }
        else if (y == 1) {
            printf(" Player HP: %-4d", playerSystem->GetHP());
        }
        else if (y == 2) {
            printf(" Player Level: %d", playerSystem->GetPlayerLevel());
        }
        else if (y == 3) {
            printf(" Player Bullet Level: %-4d", playerSystem->GetPlayerBulletLevel());
        }
        else if (y == 4) {
            printf(" Next Level: %-4d enemies left", playerSystem->GetEXPRemain());
        }

        // Show debug info if enabled
        // デバッグ情報を表示（有効時のみ）
        if (showDebugMessage) {
            if (y == 6) {
                printf(" ---DEBUG INFO---");
            }
            else if (y == 7) {
                printf(" DeltaTime: %f", myDeltaTime);
            }
            else if (y == 9) {
                printf(" Player Bullet Interval: %-4d ms", ConfigManager::GetInstance().GetPlayerInitialFireInterval() / playerSystem->GetPlayerLevel());
            }
            else if (y == 10) {
                printf(" Enemy Spawn Interval: %-4d ms", ConfigManager::GetInstance().GetEnemyBaseSpawnInterval() / playerSystem->GetPlayerLevel());
            }
            else if (y == 11) {
                printf(" HealthPack Spawn Interval: %-4d ms", ConfigManager::GetInstance().GetHealthPackSpawnInterval());
            }
            else if (y == 13) {
                printf(" ---CHEAT MODE---");
            }
            else if (y == 14) {
                printf(" Press 'H' to add HP");
            }
            else if (y == 15) {
                printf(" Press 'E' to eliminate all enemies");
            }
            else if (y == 16) {
                printf(" Press 'L' to level up player");
			}
        }

        printf("\n");
    }

    // Bottom wall
    for (int x = 0; x < ConfigManager::GetInstance().GetFieldWidth() + 2; x++) {
        putchar(X_WALL);
    }
    printf("\n");

    // Eliminated enemy count
    int liveEnemyCount = 0;
    if (enemySystem) {
        const auto& enemies = enemySystem->GetAllEnemy();
        liveEnemyCount = static_cast<int>(std::count_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e) {
                return e && !e->GetIsDead();
            }));
    }
    printf(" Eliminated enemy Count: %d", enemySystem->GetEliminatedEnemyCount());
}

// Toggle debug info display by input
// 入力でデバッグ情報表示を切り替え
void FieldManager::ShowDebugInfo(char input)
{
    switch (input)
    {
		// Show debug info and open debug mode
		// デバッグ情報を表示し、デバッグモードをONにする
        case '0':
            system("cls");
            showDebugMessage = !showDebugMessage;
            break;

		// If debug mode is on, active cheat commands
		// Debug modeがONのとき、チートコマンドを有効化
        
		// Add HP to player
		// プレイヤーにHPを追加
        case 'H':
        case 'h':
            if (showDebugMessage && playerSystem) {
                system("cls");
                playerSystem->AddHP();
            }
            break;

		// Destroy all enemies
		// すべての敵を破壊し
        case 'E':
        case 'e':
            if (showDebugMessage && enemySystem) {
                system("cls");
                for (const auto& e : enemySystem->GetAllEnemy()) {
                    if (e && !e->GetIsDead()) {
                        e->UnderAttack(e->GetHP());
                    }
                }
            }
			break;

		// Add player level
        // プレイヤーレベルを追加
        case 'L':
        case 'l':
            if (showDebugMessage && playerSystem) {
                system("cls");
                playerSystem->AddKillCount(playerSystem->GetEXPRemain());
            }
			break;
           
    default: break;
    }
}

// Countdown timer logic
// カウントダウンタイマー処理
void FieldManager::CountDownTimer()
{
    countDownTime--;
    if (countDownTime <= 0 && playerSystem)
    {
        playerSystem->UnderAttack(playerSystem->GetHP());
    }
}
