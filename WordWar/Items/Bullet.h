#pragma once
#include "../Characters/Character.h"

// Enum for bullet move direction
// �����Ƅӷ����ʾ���В���
enum class MoveDir {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

// Bullet class derived from CharacterBase
// CharacterBase ��@�Ф��������饹
class Bullet : public CharacterBase
{
public:
    // Constructor: create bullet with direction and level
    // ���󥹥ȥ饯��������ȥ�٥��ָ�����Ə�������
    Bullet(int x, int y, MoveDir dir, int bulletLevel);

    ~Bullet(); // Destructor / �ǥ��ȥ饯��

    // Update bullet position
    // ����λ�ä����
    void Update(float deltaTime);

    // Check if bullet is out of field
    // �����ե��`����⤫�_�J
    bool GetIsOutOfField();

    // Check if bullet can move this frame
    // ���Υե�`��Ǐ����Ƅӿ��ܤ��_�J
    bool CanMove(float deltaTime);
private:
    MoveDir direction;    // Bullet direction / ���η���
    bool isOutOfField;    // Out of field flag / �ե��`�����ե饰

    float moveInterval;   // Movement interval / �Ƅ��g��
    float timeAccumulator; // Time accumulator for movement / �Ƅ��Õr�g�۷e
};