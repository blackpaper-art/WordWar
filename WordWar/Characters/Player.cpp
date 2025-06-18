#include "Player.h"
#include "../Interface/IBulletSystem.h"
#include "../Items/Bullet.h"
#include "../Managers/ConfigManager.h"

#define FIELD_WIDTH (16 * 3)
#define FIELD_HEIGHT (9 * 3)

Player::Player(int x, int y, IBulletSystem* bs, TimerManager* tm)
	:
	CharacterBase(x, y, 
		ConfigManager::GetInstance().GetPlayerInitialHP(),
		1,
		ConfigManager::GetInstance().GetPlayerSymbol()[0],
		false,
		ConfigManager::GetInstance().GetPlayerInitialAP()
	),
	bulletSystem(bs),
	timerManager(tm),
	bulletLevel(1),
	level(1), 
	killCount(0), 
	nextLevelKills(10),
	bulletDir(0)
{}

Player::~Player()
{
	if (fireTimer) {
		fireTimer->isActive = false;
	}
}

void Player::Update(char input)
{
	//Movement
	int newX = CharacterBase::GetX(), newY = CharacterBase::GetY();

	switch (input)
	{
	case 'w': newY--; bulletDir = 0; break;
	case 's': newY++; bulletDir = 1; break;
	case 'a': newX--; bulletDir = 2; break;
	case 'd': newX++; bulletDir = 3; break;
	default: break;
	}

	if (newX >= 0 && newX < FIELD_WIDTH &&
		newY >= 0 && newY < FIELD_HEIGHT)
	{
		SetX(newX);
		SetY(newY);
	}
}

void Player::AddKillCount(int count)
{
	killCount += count;
	TryLevelUp();
}

void Player::TryLevelUp()
{
	int baseKills = 10;
	float growthFactor = 1.5f;

	while (killCount >= nextLevelKills)
	{
		killCount -= nextLevelKills;
		level++;
		nextLevelKills = baseKills * level * growthFactor;

		// Every 3 player level up 1 player level
		if (level % 3 == 0) {
			bulletLevel++;
		}
	}
}

void Player::FireBullets(int bLevel, int rate)
{
	//According player direction and player level to fire bullet
	//level 1: One dir (UP)
	//level 2: Two dir (UP & DOWN)
	//level 3: Four dir (UP & DOWN & LEFT & RIGHT)
	//level 4: Eight dir (UP & DOWN & LEFT & RIGHT 
	//						 & UP LEFT & UP DOWN & DOWN LEFT & DOWN RIGHT)

	if (bulletSystem)
	{
		std::vector<MoveDir> directions;

		switch (bulletDir)
		{
		case 0: // Up
			directions.push_back(MoveDir::Up);
			if (bLevel >= 2) directions.push_back(MoveDir::Down);
			if (bLevel >= 3) {
				directions.push_back(MoveDir::Left);
				directions.push_back(MoveDir::Right);
			}
			if (bLevel >= 4) {
				directions.push_back(MoveDir::UpLeft);
				directions.push_back(MoveDir::UpRight);
				directions.push_back(MoveDir::DownLeft);
				directions.push_back(MoveDir::DownRight);
			}
			break;
		case 1: // Down
			directions.push_back(MoveDir::Down);
			if (bLevel >= 2) directions.push_back(MoveDir::Up);
			if (bLevel >= 3) {
				directions.push_back(MoveDir::Left);
				directions.push_back(MoveDir::Right);
			}
			if (bLevel >= 4) {
				directions.push_back(MoveDir::UpLeft);
				directions.push_back(MoveDir::UpRight);
				directions.push_back(MoveDir::DownLeft);
				directions.push_back(MoveDir::DownRight);
			}
			break;
		case 2: // Left
			directions.push_back(MoveDir::Left);
			if (bLevel >= 2) directions.push_back(MoveDir::Right);
			if (bLevel >= 3) {
				directions.push_back(MoveDir::Up);
				directions.push_back(MoveDir::Down);
			}
			if (bLevel >= 4) {
				directions.push_back(MoveDir::UpLeft);
				directions.push_back(MoveDir::UpRight);
				directions.push_back(MoveDir::DownLeft);
				directions.push_back(MoveDir::DownRight);
			}
			break;
		case 3: // Right
			directions.push_back(MoveDir::Right);
			if (bLevel >= 2) directions.push_back(MoveDir::Left);
			if (bLevel >= 3) {
				directions.push_back(MoveDir::Up);
				directions.push_back(MoveDir::Down);
			}
			if (bLevel >= 4) {
				directions.push_back(MoveDir::UpLeft);
				directions.push_back(MoveDir::UpRight);
				directions.push_back(MoveDir::DownLeft);
				directions.push_back(MoveDir::DownRight);
			}
			break;
		default:
			directions.push_back(MoveDir::Up);
			break;
		}

		for (const auto& dir : directions)
		{
			bulletSystem->SpawnBullet(CharacterBase::GetX(), CharacterBase::GetY(), dir, bulletLevel);
		}
	}
}

//Interfaces
int Player::GetPlayerLevel()
{
	return level;
}

int Player::GetPlayerBulletLevel()
{
	return bulletLevel;
}

int Player::GetEXPRemain()
{
	return nextLevelKills - killCount;
}

int Player::GetX() const {
	return CharacterBase::GetX();
}

int Player::GetY() const {
	return CharacterBase::GetY();
}

int Player::GetHP() const {
	return CharacterBase::GetHP();
}

char Player::GetSymbol() const
{
	return CharacterBase::GetSymbol();
}

void Player::Initialize() {
	auto self = shared_from_this();
	fireTimer = timerManager->SetTimer(ConfigManager::GetInstance().GetPlayerFireInterval() / GetPlayerLevel(), [weakSelf = std::weak_ptr<Player>(self)] {
		if (auto s = weakSelf.lock()) {
			s->FireBullets(s->GetPlayerLevel(), s->level);
		}
		}, true);
}

void Player::UnderAttack(int damage) {
	CharacterBase::UnderAttack(damage);
}

void Player::AddHP()
{
	CharacterBase::SetHP(10);
}

void Player::Shutdown()
{
	if (fireTimer) {
		fireTimer->Stop();
		fireTimer.reset();
	}
}
