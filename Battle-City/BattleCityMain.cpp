#include "stdafx.h"
#include "D2DException.h"
#include "BattleCityMain.h"
#include "BattleCityObject.h"
#include "resource.h"
#include <typeinfo>

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

BattleCityMain::BattleCityMain()
{
	// �����������
	srand(time(nullptr));

	// ��ʼ�� D2D ��ͼ��Դ
	m_terrainBitmaps.fill(nullptr);
	m_armorTankBitmaps.fill(nullptr);
	m_basicTankBitmaps.fill(nullptr);
	m_fastTankBitmaps.fill(nullptr);
	m_powerTankBitmaps.fill(nullptr);
	m_playerTankBitmaps.fill(nullptr);
	m_tankLoadingBitmaps.fill(nullptr);
	m_bulletBitmaps.fill(nullptr);
	m_bulletExplosionBitmaps.fill(nullptr);
	m_bulletBigExplosionBitmaps.fill(nullptr);

	// ���ô�����Ϣ
	m_windowCaption = L"Battle City";
	m_clientWidth = 526;
	m_clientHeight = 488;
	m_fps = 120;
	m_createStruct.cx = m_clientWidth;
	m_createStruct.cy = m_clientHeight;

	// ��ʼ����Ϸ��Ϣ
	// �ؿ���Ϣ
	m_stageInfo.beginFrame = 0;
	m_stageInfo.stage = 0;
	// �˵���Ϣ
	m_menuInfo.chosenItem = GameMenuInfo::ONE_PLAYER;
	m_menuInfo.animationPlayed = false;
	m_menuInfo.beginFrame = 0;
	// ��Ϸʱ��Ϣ
	m_runningInfo.beginFrame = 0;
	m_runningInfo.score = 0;
	m_runningInfo.bGameover = false;
	m_runningInfo.explosionList.clear();
	// �з�̹����Ϣ
	m_enemyTankInfo.enemyTank.clear();
	m_enemyTankInfo.presentEnemyTank = 0;
	m_enemyTankInfo.summonedEnemyTank = 0;
	// �ҷ�̹����Ϣ
	m_playerTankInfo.playerTank = nullptr;
	m_playerTankInfo.playerLives = 0;

}

bool BattleCityMain::Init(HINSTANCE hInstance)
{
	if(!D2DApp::Init(hInstance))
		return false;

	// ������Ϸ֡��
	m_timer.SetFps(m_fps);
	
	// ������Ϸ��ʹ�õ�����
	ComPtr<IDWriteTextFormat> pTextFormat;
	ThrowIfFailed(m_pDWriteFactory->CreateTextFormat(
		L"Press Start",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		16.0,
		L"en-us",
		&pTextFormat));
	ThrowIfFailed(pTextFormat.As(&m_pTextFormat));
	pTextFormat.Reset();

	// ������ˢ
	ThrowIfFailed(m_pDirect2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrushBlack));
	ThrowIfFailed(m_pDirect2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrushWhite));
	ThrowIfFailed(m_pDirect2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_pBrushRed));
	ThrowIfFailed(m_pDirect2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pBrushGray));
	ThrowIfFailed(m_pDirect2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &m_pBrushOrange));

	// ������ͼ
	LoadingBitmaps();

	// ������Ⱦ�߳�
	thread renderThread(Render, this);
	if (m_renderThread.joinable())
	{
		m_renderThread.join();
	}
	m_renderThread.swap(renderThread);
	if (renderThread.joinable())
	{
		renderThread.join();
	}

	// ��ʼ���ز˵�
	m_gameState = GameState::GAME_MENU;
	m_menuInfo.beginFrame = m_timer.CurrentFrame();

	return true;
}

bool BattleCityMain::Release()
{
	// �ر���Ⱦ�߳�
	if (m_renderThread.joinable())
	{
		m_renderThread.join();
	}

	// �ͷ���ͼ��Դ
	ReleaseBitmaps();
	ReleaseEnemyTank();
	// �ͷŻ�ˢ��Դ
	m_pBrushWhite.Reset();
	m_pBrushRed.Reset();
	m_pBrushGray.Reset();
	m_pBrushBlack.Reset();
	m_pBrushOrange.Reset();

	return D2DApp::Release();
}

bool BattleCityMain::IsBlankPoint(const Tank *tank, Direction direction, const D2D1_POINT_2F &point)
{
	// ̹����ͼ��С��32
	// �ж�˳��
	// 1. ����߽磺ֱ�Ӽ����������Ѿ�����߽�
	// 2. ̹����ײ����з�̹�˺��ҷ�̹�˽��о�����飩�����̹�˳����ڽ������Ѿ��໥����������ô�޷������������ƶ�
	// 3. ���ͼ�з�����ײ
	switch (direction)
	{
	case Direction::LEFT:
		if (point.x < 0)
		{
			return false;
		}


		for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_destroyed || m_enemyTankInfo.enemyTank[i] == tank)
			{
				continue;
			}
			if (m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y > point.y - 32 && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y < point.y + 32
				&& m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x + 32 > point.x && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x < point.x)
			{
				return false;
			}
		}
		if ((m_playerTankInfo.playerTank != nullptr) && tank != m_playerTankInfo.playerTank && m_playerTankInfo.playerTank->m_topLeftCornerPoint.y > point.y - 32 && m_playerTankInfo.playerTank->m_topLeftCornerPoint.y < point.y + 32
			&& m_playerTankInfo.playerTank->m_topLeftCornerPoint.x + 32 > point.x && m_playerTankInfo.playerTank->m_topLeftCornerPoint.x < point.x)
		{
			return false;
		}


		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
				case TERRAIN_WALLSTEEL:
				case TERRAIN_WATER:
					if (16 * j > point.y - 16 && 16 * j < point.y + 32 && 16 * i + 16 > point.x && 16 * i < point.x && !floatEqual(16 * j, point.y - 16) && !floatEqual(16 * j, point.y + 32))
					{
						return false;
					}
				}
			}
		}

		break;

	case Direction::RIGHT:
		if (point.x > m_gameClientWidth - 32)
		{
			return false;
		}


		for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_destroyed || m_enemyTankInfo.enemyTank[i] == tank)
			{
				continue;
			}
			if (m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y > point.y - 32 && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y < point.y + 32
				&& m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x - 32 < point.x && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x > point.x)
			{
				return false;
			}
		}
		if ((m_playerTankInfo.playerTank != nullptr) && tank != m_playerTankInfo.playerTank && m_playerTankInfo.playerTank->m_topLeftCornerPoint.y > point.y - 32 && m_playerTankInfo.playerTank->m_topLeftCornerPoint.y < point.y + 32
			&& m_playerTankInfo.playerTank->m_topLeftCornerPoint.x - 32 < point.x && m_playerTankInfo.playerTank->m_topLeftCornerPoint.x > point.x)
		{
			return false;
		}


		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
				case TERRAIN_WALLSTEEL:
				case TERRAIN_WATER:
					if (j * 16 > point.y - 16 && j * 16 < point.y + 32 && i * 16 < point.x + 32 && i * 16 > point.x && !floatEqual(16 * j, point.y - 16) && !floatEqual(16 * j, point.y + 32))
					{
						return false;
					}
				}
			}
		}

		break;

	case Direction::UP:
		if (point.y < 0)
		{
			return false;
		}


		for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_destroyed || m_enemyTankInfo.enemyTank[i] == tank)
			{
				continue;
			}
			if (m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x > point.x - 32 && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x < point.x + 32
				&& m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y + 32 > point.y && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y < point.y)
			{
				return false;
			}
		}
		if ((m_playerTankInfo.playerTank != nullptr) && tank != m_playerTankInfo.playerTank && m_playerTankInfo.playerTank->m_topLeftCornerPoint.x > point.x - 32 && m_playerTankInfo.playerTank->m_topLeftCornerPoint.x < point.x + 32
			&& m_playerTankInfo.playerTank->m_topLeftCornerPoint.y + 32 > point.y && m_playerTankInfo.playerTank->m_topLeftCornerPoint.y < point.y)
		{
			return false;
		}


		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
				case TERRAIN_WALLSTEEL:
				case TERRAIN_WATER:
					if (16 * i > point.x - 16 && 16 * i < point.x + 32 && 16 * j > point.y - 16 && 16 * j < point.y && !floatEqual(16 * i, point.x - 16) && !floatEqual(16 * i, point.x + 32))
					{
						return false;
					}
				}
			}
		}
		break;

	case Direction::DOWN:
		if (point.y > m_gameClientHeight - 32)
		{
			return false;
		}


		for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_destroyed || m_enemyTankInfo.enemyTank[i] == tank)
			{
				continue;
			}
			if (m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x > point.x - 32 && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x < point.x + 32
				&& m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y - 32 < point.y && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y > point.y)
			{
				return false;
			}
		}
		if ((m_playerTankInfo.playerTank != nullptr) && tank != m_playerTankInfo.playerTank && m_playerTankInfo.playerTank->m_topLeftCornerPoint.x > point.x - 32 && m_playerTankInfo.playerTank->m_topLeftCornerPoint.x < point.x + 32
			&& m_playerTankInfo.playerTank->m_topLeftCornerPoint.y - 32 < point.y && m_playerTankInfo.playerTank->m_topLeftCornerPoint.y > point.y)
		{
			return false;
		}


		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
				case TERRAIN_WALLSTEEL:
				case TERRAIN_WATER:
					if (16 * i > point.x - 16 && 16 * i < point.x + 32 && 16 * j < point.y + 32 && 16 * j > point.y && !floatEqual(16 * i, point.x - 16) && !floatEqual(16 * i, point.x + 32))
					{
						return false;
					}
				}
			}
		}
		break;
	}
	return true;
}

bool BattleCityMain::FreshBullets()
{
	if (m_playerTankInfo.playerTank != nullptr)
	{
		if (m_playerTankInfo.playerTank->m_bullet1.m_present)
		{
			UpdateBullet(m_playerTankInfo.playerTank->m_bullet1);
		}
		if (m_playerTankInfo.playerTank->m_bullet2.m_present)
		{
			UpdateBullet(m_playerTankInfo.playerTank->m_bullet2);
		}
	}
	for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
	{
		if (m_enemyTankInfo.enemyTank[i]->m_bullet.m_present)
		{
			UpdateBullet(m_enemyTankInfo.enemyTank[i]->m_bullet);
		}
	}
	return true;
}

bool BattleCityMain::UpdateBullet(Bullet & bullet)
{
	__int64 currentFrame = m_timer.CurrentFrame();
	D2D1_POINT_2F &bulletPos = bullet.m_topLeftCornerPoint;

	// 1. �ƻ����أ��ӵ���������������ر��ݻٲ�������ը
	if (bulletPos.x >= 192 && bulletPos.x <= 192 + 32
		&& bulletPos.y >= 384)
	{
		m_runningInfo.explosionList.push_back({ true, currentFrame, D2D1::Point2F(192 - 16, 384 - 16) });
		bullet.m_present = false;
		m_baseDestroyed = true;
		return true;
	}

	// 2. �ƻ�̹�ˣ��ӵ����жԷ�̹�ˣ��ݻٶԷ�̹�˲�������ը
	// 3. �ӵ���������Է�̹�˵��ӵ�����ʱ��������������ը
	if (bullet.m_playerOwned)
	{
		for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_bullet.m_present)
			{
				if (!m_enemyTankInfo.enemyTank[i]->m_destroyed)
				{
					if (m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x < bulletPos.x && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x + 32 > bulletPos.x &&
						m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y < bulletPos.y && m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y + 32 > bulletPos.y)
					{
						ArmorTank *p = nullptr;
						if (dynamic_cast<BasicTank*>(m_enemyTankInfo.enemyTank[i]) != nullptr)
						{
							m_playerTankInfo.destroyedBasicTank++;
							if (m_enemyTankInfo.enemyTank[i]->m_haveProp&&m_playerTankInfo.playerTank->m_star < 3)
								m_playerTankInfo.playerTank->m_star++;
						}
						else if ((p = dynamic_cast<ArmorTank*>(m_enemyTankInfo.enemyTank[i])) != nullptr)
						{
							if (p->m_life == 0)
							{
								m_playerTankInfo.destroyedArmorTank++;
								m_enemyTankInfo.presentEnemyTank--;
								bullet.m_present = false;
								p->m_destroyed = true;
								m_runningInfo.explosionList.push_back({ true, currentFrame,
									D2D1::Point2F(m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x - 16,m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y - 16) });
								return true;
							}
							else
							{
								p->m_life--;
								bullet.m_present = false;
								m_runningInfo.explosionList.push_back({ false, currentFrame,
									D2D1::Point2F(m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x - 16,m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y - 16) });
								return true;
							}

						}
						else if (dynamic_cast<PowerTank*>(m_enemyTankInfo.enemyTank[i]) != nullptr)
						{
							m_playerTankInfo.destroyedPowerTank++;
						}
						else
						{
							m_playerTankInfo.destroyedFastTank++;
						}
						m_enemyTankInfo.enemyTank[i]->m_destroyed = true;
						m_enemyTankInfo.presentEnemyTank--;
						
						m_runningInfo.explosionList.push_back({ true, currentFrame,
							D2D1::Point2F(m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x - 16,m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y - 16) });
						bullet.m_present = false;
					}
				}

				if (abs(m_enemyTankInfo.enemyTank[i]->m_bullet.m_topLeftCornerPoint.x - bullet.m_topLeftCornerPoint.x) <= 8
					&& abs(m_enemyTankInfo.enemyTank[i]->m_bullet.m_topLeftCornerPoint.y - bullet.m_topLeftCornerPoint.y) <= 8)
				{
					m_enemyTankInfo.enemyTank[i]->m_bullet.m_present = bullet.m_present = false;
					return true;
				}
			}
		}

	}
	else
	{
		if ((m_playerTankInfo.playerTank != nullptr) && IntersectionNotEmpty(m_playerTankInfo.playerTank->m_topLeftCornerPoint.x, m_playerTankInfo.playerTank->m_topLeftCornerPoint.x + 32, bulletPos.x, bulletPos.x + 8) &&
			IntersectionNotEmpty(m_playerTankInfo.playerTank->m_topLeftCornerPoint.y, m_playerTankInfo.playerTank->m_topLeftCornerPoint.y + 32, bulletPos.y, bulletPos.y + 8))
		{
			m_runningInfo.explosionList.push_back({ true, currentFrame, m_playerTankInfo.playerTank->m_topLeftCornerPoint });
			bullet.m_present = false;
			SummonTank(false);
		}

		if ((m_playerTankInfo.playerTank != nullptr) && abs(m_playerTankInfo.playerTank->m_bullet1.m_topLeftCornerPoint.x - bullet.m_topLeftCornerPoint.x) <= 8
			&& abs(m_playerTankInfo.playerTank->m_bullet1.m_topLeftCornerPoint.y - bullet.m_topLeftCornerPoint.y) <= 8)
		{
			m_playerTankInfo.playerTank->m_bullet1.m_present = bullet.m_present = false;
			return true;
		}

		if ((m_playerTankInfo.playerTank != nullptr) && abs(m_playerTankInfo.playerTank->m_bullet2.m_topLeftCornerPoint.x - bullet.m_topLeftCornerPoint.x) <= 8
			&& abs(m_playerTankInfo.playerTank->m_bullet2.m_topLeftCornerPoint.y - bullet.m_topLeftCornerPoint.y) <= 8)
		{
			m_playerTankInfo.playerTank->m_bullet2.m_present = bullet.m_present = false;
			return true;
		}

	}

	// 4. ����߽磺ֱ�Ӽ����������Ѿ�����߽磬�ӵ����ݻٲ�����С�ͱ�ը
	// 5. �ƻ����飺�ӵ����пɴݻٷ��飨��ש��ȣ����ݻٷ��鲢����С�ͱ�ը
	bool bulletDestroyed = false;
	switch (bullet.m_direction)
	{
	case Direction::LEFT:
		if (bulletPos.x < 0)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 32, bulletPos.y - 24) });
			return true;
		}

		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
					if ((16 * i < bulletPos.x && 16 * i + 16 > bulletPos.x) &&
						((bulletPos.y + 8 > 16 * j + 16 && 16 * j + 16 >= bulletPos.y) ||
						(16 * j + 16 > bulletPos.y + 8 && bulletPos.y + 8 >= 16 * j)))
					{
						m_runningInfo.terrain[j][i] = TERRAIN_GROUND;
						bulletDestroyed = true;
					}
					break;
				case TERRAIN_WALLSTEEL:
					if ((16 * i < bulletPos.x && 16 * i + 16 > bulletPos.x) &&
						((bulletPos.y + 8 > 16 * j + 16 && 16 * j + 16 >= bulletPos.y) ||
						(16 * j + 16 > bulletPos.y + 8 && bulletPos.y + 8 >= 16 * j)))
					{
						bulletDestroyed = true;
					}
					break;
				}
			}
		}
		if (bulletDestroyed)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 32, bulletPos.y - 24) });
			return true;
		}
		
		break;

	case Direction::RIGHT:
		if (bulletPos.x > m_gameClientWidth - 8)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 24, bulletPos.y - 24) });
			return true;
		}
		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
					if ((16 * i<bulletPos.x && 16 * i + 16>bulletPos.x) &&
						((bulletPos.y + 8 > 16 * j + 16 && 16 * j + 16 >= bulletPos.y) ||
						(16 * j + 16 > bulletPos.y + 8 && bulletPos.y + 8 >= 16 * j)))
					{
						m_runningInfo.terrain[j][i] = TERRAIN_GROUND;
						bulletDestroyed = true;
					}
					break;
				case TERRAIN_WALLSTEEL:
					if ((16 * i < bulletPos.x && 16 * i + 16 > bulletPos.x) &&
						((bulletPos.y + 8 > 16 * j + 16 && 16 * j + 16 >= bulletPos.y) ||
						(16 * j + 16 > bulletPos.y + 8 && bulletPos.y + 8 >= 16 * j)))
					{
						bulletDestroyed = true;
					}
					break;
				}
			}
		}
		if (bulletDestroyed)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 24, bulletPos.y - 24) });
			return true;
		}

		
		break;

	case Direction::UP:
		if (bulletPos.y < 0)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 28, bulletPos.y - 32) });
			return true;
		}

		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
					if ((16 * j < bulletPos.y && 16 * j + 16 > bulletPos.y) &&
						((bulletPos.x + 8 > 16 * i + 16 && 16 * i + 16 >= bulletPos.x) ||
						(16 * i + 16 > bulletPos.x + 8 && bulletPos.x + 8 >= 16 * i)))
					{
						m_runningInfo.terrain[j][i] = TERRAIN_GROUND;
						bulletDestroyed = true;
					}
					break;
				case TERRAIN_WALLSTEEL:
					if ((16 * j < bulletPos.y && 16 * j + 16 > bulletPos.y) &&
						((bulletPos.x + 8 > 16 * i + 16 && 16 * i + 16 >= bulletPos.x) ||
						(16 * i + 16 > bulletPos.x + 8 && bulletPos.x + 8 >= 16 * i)))
					{
						bulletDestroyed = true;
					}
					break;
				}
			}
		}
		if (bulletDestroyed)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 28, bulletPos.y - 32) });
			return true;
		}

		
		break;

	case Direction::DOWN:
		if (bulletPos.y > m_gameClientHeight - 8)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 28, bulletPos.y - 24) });
			return true;
		}

		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				switch (m_runningInfo.terrain[j][i])
				{
				case TERRAIN_WALLBLICK:
					if ((16 * j < bulletPos.y && 16 * j + 16 > bulletPos.y) &&
						((bulletPos.x + 8 > 16 * i + 16 && 16 * i + 16 >= bulletPos.x) ||
						(16 * i + 16 > bulletPos.x + 8 && bulletPos.x + 8 >= 16 * i)))
					{
						m_runningInfo.terrain[j][i] = TERRAIN_GROUND;
						bulletDestroyed = true;
					}
					break;
				case TERRAIN_WALLSTEEL:
					if ((16 * j < bulletPos.y && 16 * j + 16 > bulletPos.y) &&
						((bulletPos.x + 8 > 16 * i + 16 && 16 * i + 16 >= bulletPos.x) ||
						(16 * i + 16 > bulletPos.x + 8 && bulletPos.x + 8 >= 16 * i)))
					{
						bulletDestroyed = true;
					}
					break;
				}
			}
		}
		if (bulletDestroyed)
		{
			bullet.m_present = false;
			m_runningInfo.explosionList.push_back({ false, currentFrame, D2D1::Point2F(bulletPos.x - 28, bulletPos.y - 24) });
			return true;
		}

		break;
	}
	return false;
}

bool BattleCityMain::LoadingBitmaps()
{
	// ������Ϸ�˵�������ͼ
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_BATTLECITY), BITMAP_RESOURCE_TYPE, 376, 136, &m_battleCityBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_NAMCOT), BITMAP_RESOURCE_TYPE, 142, 16, &m_namcotBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_COPYRIGHT), BITMAP_RESOURCE_TYPE, 16, 16, &m_copyrightBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_ROMAN_ONE_WHITE), BITMAP_RESOURCE_TYPE, 8, 14, &m_romanOneWhiteBitmap);

	// ������Ϸʱ��Ϣ����ͼ
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_FLAG), BITMAP_RESOURCE_TYPE, 32, 32, &m_stageFlagBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_ROMAN_ONE), BITMAP_RESOURCE_TYPE, 8, 14, &m_romanOneBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_LIVES), BITMAP_RESOURCE_TYPE, 16, 16, &m_playerLivesBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_ENEMY), BITMAP_RESOURCE_TYPE, 16, 16, &m_enemyNumBitmap);

	// ������Ϸ����������ͼ
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_GAMEOVER), BITMAP_RESOURCE_TYPE, 248, 160, &m_gameoverBitmap);

	// ������Ϸ���������ͼ
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_ROMAN_ONE_RED), BITMAP_RESOURCE_TYPE, 8, 14, &m_romanOneRedBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_WHITELINE), BITMAP_RESOURCE_TYPE, 128, 4, &m_whiteLineBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_ARROW), BITMAP_RESOURCE_TYPE, 14, 14, &m_arrowBitmap);

	// ���ص�����ͼ
	for (int i = 0; i < 2; ++i)
	{
		LoadBitmapFromResource(MAKEINTRESOURCE(TERRAIN_BEGIN + i), BITMAP_RESOURCE_TYPE, 16, 16, &m_terrainBitmaps[i]);
	}
	for (int i = 2; i < 5; ++i)
	{
		LoadBitmapFromResource(MAKEINTRESOURCE(TERRAIN_BEGIN + i), BITMAP_RESOURCE_TYPE, 32, 32, &m_terrainBitmaps[i]);
	}

	// ���ػ�����ͼ
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_BASE), BITMAP_RESOURCE_TYPE, 16, 16, &m_baseBitmap);
	LoadBitmapFromResource(MAKEINTRESOURCE(IDB_PNG_BASE_DESTROYED), BITMAP_RESOURCE_TYPE, 16, 16, &m_baseDestroyedBitmap);

	// ��������ս����ͼ
	int t = 0;
	for (int i = 0; i < 4; i++)// ������ɫ
	{
		for (int j = 0; j < 4; j++)// �ĸ�����
		{
			LoadBitmapFromResource(MAKEINTRESOURCE(ARMOR_TANK_BEGIN + i * 100 + j * 10), BITMAP_RESOURCE_TYPE, 32, 32, &m_armorTankBitmaps[t]);
			LoadBitmapFromResource(MAKEINTRESOURCE(ARMOR_TANK_BEGIN + i * 100 + j * 10 + 1), BITMAP_RESOURCE_TYPE, 32, 32, &m_armorTankBitmaps[t + 1]);
			t += 2;
		}
	}

	// ������̹ͨ����ͼ
	t = 0;
	for (int i = 0; i < 2; i++)// ������ɫ
	{
		for (int j = 0; j < 4; j++)// �ĸ�����
		{
			LoadBitmapFromResource(MAKEINTRESOURCE(BASIC_TANK_BEGIN + i * 100 + j * 10), BITMAP_RESOURCE_TYPE, 32, 32, &m_basicTankBitmaps[t]);
			LoadBitmapFromResource(MAKEINTRESOURCE(BASIC_TANK_BEGIN + i * 100 + j * 10 + 1), BITMAP_RESOURCE_TYPE, 32, 32, &m_basicTankBitmaps[t + 1]);
			t += 2;
		}
	}

	// ������������ͼ
	t = 0;
	for (int i = 0; i < 2; i++)// ������ɫ
	{
		for (int j = 0; j < 4; j++)// �ĸ�����
		{
			LoadBitmapFromResource(MAKEINTRESOURCE(FAST_TANK_BEGIN + i * 100 + j * 10), BITMAP_RESOURCE_TYPE, 32, 32, &m_fastTankBitmaps[t]);
			LoadBitmapFromResource(MAKEINTRESOURCE(FAST_TANK_BEGIN + i * 100 + j * 10 + 1), BITMAP_RESOURCE_TYPE, 32, 32, &m_fastTankBitmaps[t + 1]);
			t += 2;
		}
	}

	// ����װ�׳���ͼ
	t = 0;
	for (int i = 0; i < 2; i++)// ������ɫ
	{
		for (int j = 0; j < 4; j++)// �ĸ�����
		{
			LoadBitmapFromResource(MAKEINTRESOURCE(POWER_TANK_BEGIN + i * 100 + j * 10), BITMAP_RESOURCE_TYPE, 32, 32, &m_powerTankBitmaps[t]);
			LoadBitmapFromResource(MAKEINTRESOURCE(POWER_TANK_BEGIN + i * 100 + j * 10 + 1), BITMAP_RESOURCE_TYPE, 32, 32, &m_powerTankBitmaps[t + 1]);
			t += 2;
		}
	}

	// �������̹����ͼ
	t = 0;
	for (int i = 0; i < 4; i++)// �ĸ��ȼ�
	{
		for (int j = 0; j < 4; j++)// �ĸ�����
		{
			LoadBitmapFromResource(MAKEINTRESOURCE(PLAYER_TANK_BEGIN + i * 100 + j * 10), BITMAP_RESOURCE_TYPE, 32, 32, &m_playerTankBitmaps[t]);
			LoadBitmapFromResource(MAKEINTRESOURCE(PLAYER_TANK_BEGIN + i * 100 + j * 10 + 1), BITMAP_RESOURCE_TYPE, 32, 32, &m_playerTankBitmaps[t + 1]);
			t += 2;
		}
	}

	// ����̹�˵ǳ���ͼ
	for (int i = IDB_PNG_TANK_LOADING_1; i <= IDB_PNG_TANK_LOADING_4; i++)
	{
		LoadBitmapFromResource(MAKEINTRESOURCE(i), BITMAP_RESOURCE_TYPE, 32, 32, &m_tankLoadingBitmaps[i - IDB_PNG_TANK_LOADING_1]);
	}

	// �����ӵ���ͼ
	for (int i = IDB_PNG_BULLET_RIGHT; i <= IDB_PNG_BULLET_DOWN; i++)
	{
		LoadBitmapFromResource(MAKEINTRESOURCE(i), BITMAP_RESOURCE_TYPE, 8, 8, &m_bulletBitmaps[i - IDB_PNG_BULLET_RIGHT]);
	}

	// �����ӵ���ը��ͼ
	for (int i = IDB_PNG_BULLET_EXPLOSION_1; i <= IDB_PNG_BULLET_EXPLOSION_3; i++)
	{
		LoadBitmapFromResource(MAKEINTRESOURCE(i), BITMAP_RESOURCE_TYPE, 32, 32, &m_bulletExplosionBitmaps[i - IDB_PNG_BULLET_EXPLOSION_1]);
	}
	for (int i = IDB_PNG_BULLET_BIG_EXPLOSION_1; i <= IDB_PNG_BULLET_BIG_EXPLOSION_5; i++)
	{
		LoadBitmapFromResource(MAKEINTRESOURCE(i), BITMAP_RESOURCE_TYPE, 64, 64, &m_bulletBigExplosionBitmaps[i - IDB_PNG_BULLET_BIG_EXPLOSION_1]);
	}
	return true;
}

bool BattleCityMain::ReleaseBitmaps()
{
	ReleaseEnemyTank();

	// �ͷ���Ϸ�˵�������ͼ��Դ
	m_battleCityBitmap.Reset();
	m_namcotBitmap.Reset();
	m_copyrightBitmap.Reset();
	m_romanOneWhiteBitmap.Reset();

	// �ͷ���Ϸʱ��Ϣ����ͼ��Դ
	m_stageFlagBitmap.Reset();
	m_romanOneBitmap.Reset();
	m_playerLivesBitmap.Reset();
	m_enemyNumBitmap.Reset();

	// �ͷ���Ϸ����������ͼ��Դ
	m_gameoverBitmap.Reset();

	// �ͷ���Ϸ���������ͼ��Դ
	m_romanOneRedBitmap.Reset();
	m_whiteLineBitmap.Reset();
	m_arrowBitmap.Reset();

	// �ͷŵ�����ͼ��Դ
	ReleaseBitmapsInArray(m_terrainBitmaps);

	// �ͷŻ�����ͼ��Դ
	m_baseBitmap.Reset();
	m_baseDestroyedBitmap.Reset();

	// �ͷ�̹����ͼ��Դ
	ReleaseBitmapsInArray(m_armorTankBitmaps);	// ����ս��
	ReleaseBitmapsInArray(m_basicTankBitmaps);	// ��̹ͨ��
	ReleaseBitmapsInArray(m_fastTankBitmaps);	// ������
	ReleaseBitmapsInArray(m_powerTankBitmaps);	// װ�׳�
	ReleaseBitmapsInArray(m_playerTankBitmaps);	// ���̹��

	// �ͷ�̹�˵ǳ���ͼ��Դ
	ReleaseBitmapsInArray(m_tankLoadingBitmaps);

	// �ͷ��ӵ���ͼ��Դ
	ReleaseBitmapsInArray(m_bulletBitmaps);

	// �ͷ��ӵ���ը��ͼ��Դ
	ReleaseBitmapsInArray(m_bulletExplosionBitmaps);
	ReleaseBitmapsInArray(m_bulletBigExplosionBitmaps);
	return true;
}

// TODO
void BattleCityMain::SummonTank(bool isEnemy)
{
	if (isEnemy)
	{
		if (m_enemyTankInfo.summonedEnemyTank < m_enemyTankInfo.enemyTank.size())
		{
			m_enemyTankInfo.enemyTank[m_enemyTankInfo.summonedEnemyTank]->m_summonedFrame = m_timer.CurrentFrame();
			m_enemyTankInfo.summonedEnemyTank++;
			m_enemyTankInfo.presentEnemyTank++;
		}
	}
	else
	{
		if (m_playerTankInfo.playerLives > 0)
		{
			m_playerTankInfo.playerLives--;
			m_playerTankInfo.playerTank->m_initing = true;
			m_playerTankInfo.playerTank->m_invincible = true;
			m_playerTankInfo.playerTank->m_movable = false;
			m_playerTankInfo.playerTank->m_topLeftCornerPoint = D2D1::Point2F(4.0f * 32.0f, 12.0f * 32.0f);
			m_playerTankInfo.playerTank->m_summonedFrame = m_timer.CurrentFrame();
		}
		else if(!m_runningInfo.bGameover)
		{
			m_runningInfo.bGameover = true;
			m_runningInfo.overFrame = m_timer.CurrentFrame();
			delete m_playerTankInfo.playerTank;
			m_playerTankInfo.playerTank = nullptr;
		}
	}
}

LRESULT BattleCityMain::OnDestroy()
{
	m_gameState = GameState::GAME_CLOSING;
	return D2DApp::OnDestroy();
}

LRESULT BattleCityMain::OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (m_gameState)
	{
	case GameState::GAME_MENU:
		if (nChar == VK_RETURN)
		{
			if (!m_menuInfo.animationPlayed)
			{
				m_menuInfo.animationPlayed = true;
			}
			else
			{
				m_gameState = GameState::GAME_BEGIN;
			}
		}
		break;

	case GameState::GAME_RUNNING:
		if (nChar == VK_RETURN)
		{
			m_runningInfo.pauseFrame = m_timer.CurrentFrame();
			m_bPaused = true;
			m_gameState = GameState::GAME_PAUSE;
		}
		else if (nChar == VK_SPACE)
		{
			if (m_playerTankInfo.playerTank != nullptr)
				m_playerTankInfo.playerTank->Shot();
		}
		break;

	case GameState::GAME_PAUSE:
		if (nChar == VK_RETURN)
		{
			m_bPaused = false;
			m_gameState = GameState::GAME_RUNNING;
		}
		break;
	}

	m_bHandled = true;
	return 0;
}

void Render(BattleCityMain *gameMain)
{
	while (gameMain->m_gameState != GameState::GAME_CLOSING)
	{
		gameMain->m_timer.BeginCountFps();
		gameMain->m_timer.Tick();
		gameMain->CalculateFrameStats();
		if (!gameMain->m_bPaused)
		{
			gameMain->UpdateScene();
		}
		gameMain->DrawScene();
		gameMain->m_timer.WaitForFps();
	}
}

#pragma warning(pop)