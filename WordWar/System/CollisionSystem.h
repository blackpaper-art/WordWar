#pragma once

class IBulletSystem;
class IEnemySystem;
class IPlayerSystem;
class IHealthPackSystem;

// System for handling all in-game collisions
// ���`���ڤ��nͻ�ж���I���륷���ƥ�
class CollisionSystem
{
public:
    // Handle collisions between player, bullets, enemies, and health packs
    // �ץ쥤��`�����������؏ͥ����ƥ��g���nͻ��I��
    void HandleCollision(
        IPlayerSystem* ps,
        IBulletSystem* bs,
        IEnemySystem* es,
        IHealthPackSystem* hp);
};
