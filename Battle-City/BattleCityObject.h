#ifndef BATTLECITYOBJECT_H
#define BATTLECITYOBJECT_H

#define BITMAP_RESOURCE_TYPE					L"PNG"
#define SOUND_RESOURCE_TYPE						L"WAV"

const int TERRAIN_BEGIN = 1001;
const int TERRAIN_BITMAP_NUM = 5;

const int ARMOR_TANK_BEGIN = 2001;
const int ARMOR_TANK_BITMAP_NUM = 32;

const int BASIC_TANK_BEGIN = 3001;
const int BASIC_TANK_BITMAP_NUM = 16;

const int FAST_TANK_BEGIN = 4001;
const int FAST_TANK_BITMAP_NUM = 16;

const int POWER_TANK_BEGIN = 5001;
const int POWER_TANK_BITMAP_NUM = 16;

const int PLAYER_TANK_BEGIN = 6001;
const int PLAYER_TANK_BITMAP_NUM = 32;

#include "BattleCityMain.h"

enum TerrainType :UINT
{
	TERRAIN_WALLBLICK = 0,
	TERRAIN_WALLSTEEL = 1,
	TERRAIN_TREES = 2,
	TERRAIN_WATER = 3,
	TERRAIN_GROUND = 4,
	TERRAIN_BASE = 5
};

enum class Direction :UINT
{
	RIGHT = 0,
	LEFT = 1,
	UP = 2,
	DOWN = 3
};

enum class EnemyTankType :UINT
{
	ARMOR_TANK = 2,
	BASIC_TANK = 3,
	FAST_TANK = 4,
	POWER_TANK = 5
};

class BattleCityMain;

struct Bullet
{
	Bullet(int star)
	{
		m_star = star;
		m_present = false;

		if (star >= 1)
		{
			m_speedPerFrame = 9.0f * 32.0f / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
		}
		else
		{
			m_speedPerFrame = 7.0f * 32.0f / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
		}
	}

	virtual void GoToNextPoint();

	D2D1_POINT_2F			m_topLeftCornerPoint;
	Direction				m_direction;
	int						m_star;
	float					m_speedPerFrame;
	bool					m_playerOwned;
	bool					m_present;
};

#pragma region 坦克类声明部分

struct Tank
{
	Tank();

	virtual void GoToNextPoint(__int64 currentFrame);
	virtual void Shot() = 0;

	bool					m_isGoing;
	bool					m_movable;
	bool					m_initing;
	bool					m_invincible;
	int						m_destroyedTime;
	__int64					m_summonedFrame;
	float					m_speedPerFrame;
	Direction				m_direction;
	D2D1_POINT_2F			m_topLeftCornerPoint;
	BattleCityMain			*m_gameMain;
};

struct PlayerTank : public Tank
{
	PlayerTank():m_bullet1(0),m_bullet2(0)
	{
		m_direction = Direction::UP;
		m_topLeftCornerPoint = D2D1::Point2F(4.0f * 32.0f, 12.0f * 32.0f);
		m_speedPerFrame = 3 * 32 / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
		m_star = 0;
	}

	void Shot()override;

	UINT			m_star;
	Bullet			m_bullet1;
	Bullet			m_bullet2;
};

struct EnemyTank : public Tank
{
	EnemyTank():m_bullet(0)
	{
		m_destroyed = false;
		m_haveProp = false;
		m_topLeftCornerPoint = D2D1::Point2F(((s_bornPoint++) % 3) * 6.0f * 32.0f, 0.0f);
	}

	void GoToNextPoint(__int64 currentFrame)override;
	void Shot()override;
	virtual void f(){}
	static int		s_bornPoint;
	bool			m_destroyed;
	EnemyTankType	m_type;
	bool			m_haveProp;
	Bullet			m_bullet;
};

struct BasicTank : public EnemyTank
{
	BasicTank()
	{
		m_type = EnemyTankType::BASIC_TANK;
		m_direction = Direction::DOWN;
		m_speedPerFrame = 2 * 32 / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
	}

	virtual void f() {}
};

struct FastTank :public EnemyTank
{
	FastTank()
	{
		m_type = EnemyTankType::FAST_TANK;
		m_direction = Direction::DOWN;
		m_speedPerFrame = 5 * 32 / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
	}

	virtual void f() {}
};

struct PowerTank :public EnemyTank
{
	PowerTank()
	{
		m_type = EnemyTankType::POWER_TANK;
		m_direction = Direction::DOWN;
		m_speedPerFrame = 2 * 32 / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
	}

	virtual void f() {}
};

struct ArmorTank :public EnemyTank
{
	ArmorTank()
	{
		m_type = EnemyTankType::ARMOR_TANK;
		m_direction = Direction::DOWN;
		m_speedPerFrame = 2 * 32 / static_cast<float>(D2DAPP::D2DApp::GetApp()->GetFps());
		m_life = 3;
	}

	virtual void f() {}
	int m_life;
};
#pragma endregion


#endif // !BLOCK_H
