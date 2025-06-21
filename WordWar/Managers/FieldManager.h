#pragma once
#include "TimerManager.h"

#include <stdio.h>
#include <memory>
#include <vector>

#define X_WALL 'X'      // Wall character X side / �������
#define Y_WALL 'Y'      // Wall character Y side / �k������
#define FIELD_NULL ' '  // Empty space character / �հ�����

class EnemyManager;
class TimerManager;
class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class IHealthPackSystem;

// Manager for the entire game field
// ���`��ե��`���ȫ��������ޥͩ`����`���饹
class FieldManager : public std::enable_shared_from_this<FieldManager>
{
public:
    std::shared_ptr<TimerHandle> countDownTimer; // Countdown timer / ������ȥ����󥿥��ީ`

    FieldManager();   // Constructor / ���󥹥ȥ饯��
    ~FieldManager();  // Destructor / �ǥ��ȥ饯��

    const int GetFieldWidth() { return fieldWidth; }   // Get field width / �ե��`��ɷ�ȡ��
    const int GetFieldHeight() { return fieldHeight; } // Get field height / �ե��`��ɸߤ�ȡ��

    void InitializeManagers(
        IPlayerSystem* ps,
        IEnemySystem* es,
        IBulletSystem* bs,
        IHealthPackSystem* hps,
        TimerManager* tm); // Initialize subsystems / �����֥����ƥ���ڻ�

    void Update(float deltaTime);   // Update state / ״�B����
    void DrawField();               // Render field / �ե��`����軭
    void ShowDebugInfo(char input); // Toggle debug info by input / �����ǥǥХå���ʾ����

private:
    IEnemySystem* enemySystem;         // Enemy system reference / �������ƥ����
    IPlayerSystem* playerSystem;       // Player system reference / �ץ쥤��`�����ƥ����
    IBulletSystem* bulletSystem;       // Bullet system reference / �������ƥ����
    IHealthPackSystem* healthPackSystem; // Health pack system reference / �؏ͥ����ƥॷ���ƥ����

    int fieldWidth;   // Field width / �ե��`��ɷ�
    int fieldHeight;  // Field height / �ե��`��ɸߤ�
    std::vector<std::vector<char>> fieldBuffer; // Render buffer / �軭�Хåե�

    void CountDownTimer(); // Countdown timer logic / ������ȥ�����I��
    int countDownTime;     // Remaining time / �Ф�r�g
    float myDeltaTime;     // Delta time for debug / �ǥХå��åǥ륿������

    bool showDebugMessage; // Debug info toggle flag / �ǥХå���ʾ�ե饰
};
