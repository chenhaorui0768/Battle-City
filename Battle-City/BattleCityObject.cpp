#include "stdafx.h"
#include "D2DApp.h"
#include "BattleCityMain.h"
#include "BattleCityObject.h"

inline void FixShottedBullet(Bullet&bullet)
{
	switch (bullet.m_direction)
	{
	case Direction::RIGHT:
		bullet.m_topLeftCornerPoint.x += 24;
		bullet.m_topLeftCornerPoint.y += 12;
		break;
	case Direction::LEFT:
		bullet.m_topLeftCornerPoint.y += 12;
		break;
	case Direction::UP:
		bullet.m_topLeftCornerPoint.x += 12;
		break;
	case Direction::DOWN:
		bullet.m_topLeftCornerPoint.x += 12;
		bullet.m_topLeftCornerPoint.y += 24;
		break;
	}
}

int EnemyTank::s_bornPoint = 1;

Tank::Tank()
{
	m_destroyedTime = 0;
	m_summonedFrame = 0;
	m_movable = false;
	m_invincible = true;
	m_initing = true;
	m_gameMain = dynamic_cast<BattleCityMain*>(D2DAPP::D2DApp::GetApp());
	m_isGoing = true;
}

void Tank::GoToNextPoint(__int64 currentFrame)
{
	if (!m_isGoing || m_initing || !m_movable)
	{
		return;
	}

	float dx = 0.0f, dy = 0.0f;
	switch (m_direction)
	{
	case Direction::RIGHT:
		dx = m_speedPerFrame;
		break;
	case Direction::LEFT:
		dx = -m_speedPerFrame;
		break;
	case Direction::UP:
		dy = -m_speedPerFrame;
		break;
	case Direction::DOWN:
		dy = m_speedPerFrame;
		break;
	}
	D2D1_POINT_2F nextPoint = D2D1::Point2F(m_topLeftCornerPoint.x + dx, m_topLeftCornerPoint.y + dy);

	if (m_gameMain->IsBlankPoint(this, m_direction, nextPoint))
	{
		m_topLeftCornerPoint = nextPoint;
	}
}

void EnemyTank::GoToNextPoint(__int64 currentFrame)
{
	Shot();
	if (currentFrame % 60 == 0)
	{

		int i = rand() % 10;
		float dx = m_topLeftCornerPoint.x - 192;
		float dy = m_topLeftCornerPoint.y - 384;
		if (dx < 0)
		{
			if (dy < 0)
			{
				if (i <= 4)
					m_direction = Direction::DOWN;
				else if (i <= 7)
					m_direction = Direction::RIGHT;
				else if (i == 8)
					m_direction = Direction::LEFT;
				else
					m_direction = Direction::UP;
			}
			else
			{
				if (i <= 5)
					m_direction = Direction::RIGHT;
				else if (i <= 7)
					m_direction = Direction::DOWN;
				else if (i == 8)
					m_direction = Direction::LEFT;
				else
					m_direction = Direction::UP;
			}
		}
		else
		{
			if (dy < 0)
			{
				if (i <= 4)
					m_direction = Direction::DOWN;
				else if (i <= 7)
					m_direction = Direction::LEFT;
				else if (i == 8)
					m_direction = Direction::RIGHT;
				else
					m_direction = Direction::UP;
			}
			else
			{
				if (i <= 5)
					m_direction = Direction::LEFT;
				else if (i <= 7)
					m_direction = Direction::DOWN;
				else if (i == 8)
					m_direction = Direction::RIGHT;
				else
					m_direction = Direction::UP;
			}
		}
	}
	Tank::GoToNextPoint(currentFrame);
}

void EnemyTank::Shot()
{
	if (m_initing)
		return;

	if (!m_bullet.m_present)
	{
		m_bullet.m_playerOwned = false;
		m_bullet.m_direction = m_direction;
		m_bullet.m_present = true;
		m_bullet.m_topLeftCornerPoint = m_topLeftCornerPoint;
		FixShottedBullet(m_bullet);
	}
}

void PlayerTank::Shot()
{
	if (m_initing)
		return;

	if (!m_bullet1.m_present)
	{
		m_bullet1.m_playerOwned = true;
		m_bullet1.m_direction = m_direction;
		m_bullet1.m_present = true;
		m_bullet1.m_topLeftCornerPoint = m_topLeftCornerPoint;
		FixShottedBullet(m_bullet1);
	}

	if (m_star >= 2)
	{
		if (!m_bullet2.m_present)
		{
			m_bullet2.m_playerOwned = true;
			m_bullet2.m_direction = m_direction;
			m_bullet2.m_present = true;
			m_bullet2.m_topLeftCornerPoint = m_topLeftCornerPoint;
			FixShottedBullet(m_bullet2);
		}
	}
}

void Bullet::GoToNextPoint()
{
	if (!m_present)
	{
		return;
	}

	float dx = 0.0f, dy = 0.0f;
	switch (m_direction)
	{
	case Direction::RIGHT:
		dx = m_speedPerFrame;
		break;
	case Direction::LEFT:
		dx = -m_speedPerFrame;
		break;
	case Direction::UP:
		dy = -m_speedPerFrame;
		break;
	case Direction::DOWN:
		dy = m_speedPerFrame;
		break;
	}

	D2D1_POINT_2F nextPoint = D2D1::Point2F(m_topLeftCornerPoint.x + dx, m_topLeftCornerPoint.y + dy);
	m_topLeftCornerPoint = nextPoint;
}
