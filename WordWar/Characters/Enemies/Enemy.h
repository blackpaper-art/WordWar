#pragma once

#include "../Character.h"
#include "../../Characters/Player.h"

// Enemy character class
// ������饯���`���饹
class Enemy : public CharacterBase
{
public:
    Enemy(int x, int y, IPlayerSystem* ps); // Constructor / ���󥹥ȥ饯��
    ~Enemy();                               // Destructor / �ǥ��ȥ饯��

    // Check if enemy can move based on elapsed time
    // �U�^�r�g�˻��Ť����Ƅӿ��ܤ��ж�
    bool CanMove(float deltaTime);

    // Predict next position towards player
    // �ץ쥤��`���򤫤äƴΤ�λ�ä���y
    void PredicNextPos(int& outX, int& outY) const;

private:
    IPlayerSystem* playerSystem; // Reference to player system / �ץ쥤��`������
    float moveInterval;          // Movement interval (ms) / �Ƅ��g��
    float timeAccumulator;       // Time accumulator for movement / �Ƅ��Õr�g�۷e
};
