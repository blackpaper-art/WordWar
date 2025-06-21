#include "Enemy.h"

// Constructor: initialize enemy position and movement interval
// ���󥹥ȥ饯��������λ�ä��Ƅ��g������ڻ�
Enemy::Enemy(int x, int y, IPlayerSystem* ps)
    : CharacterBase(x, y, 1, 1, 'i', false, 1),
    playerSystem(ps),
    moveInterval(1000.0f),
    timeAccumulator(0.0f)
{
}

// Destructor
// �ǥ��ȥ饯��
Enemy::~Enemy() {}

// Check if enough time has passed to move
// һ���r�g�U�^����Ƅӿ��ܤ��ж�
bool Enemy::CanMove(float deltaTime)
{
    timeAccumulator += deltaTime;
    if (timeAccumulator >= moveInterval)
    {
        timeAccumulator = 0.0f;
        return true;
    }
    return false;
}

// Predict next position by stepping one step closer to player
// �ץ쥤��`���򤫤ä�1���ƥå��Ƅ��Ȥ���y
void Enemy::PredicNextPos(int& outX, int& outY) const
{
    outX = GetX();
    outY = GetY();

    if (playerSystem->GetX() > outX) outX++;
    else if (playerSystem->GetX() < outX) outX--;

    if (playerSystem->GetY() > outY) outY++;
    else if (playerSystem->GetY() < outY) outY--;
}
