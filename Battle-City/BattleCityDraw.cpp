#include "stdafx.h"
#include "D2DException.h"
#include "BattleCityMain.h"
#include "BattleCityObject.h"
#include "resource.h"

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

void BattleCityMain::DrawBullet()
{
	for (auto&p : m_enemyTankInfo.enemyTank)
	{
		Bullet& bullet = p->m_bullet;

		if (bullet.m_present)
		{
			DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_bulletBitmaps[static_cast<UINT>(bullet.m_direction)].Get(),
				bullet.m_topLeftCornerPoint.x, bullet.m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
		}

	}
	if (m_playerTankInfo.playerTank != nullptr)
	{
		if (m_playerTankInfo.playerTank->m_bullet1.m_present)
		{
			DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_bulletBitmaps[static_cast<UINT>(m_playerTankInfo.playerTank->m_bullet1.m_direction)].Get(),
				m_playerTankInfo.playerTank->m_bullet1.m_topLeftCornerPoint.x, m_playerTankInfo.playerTank->m_bullet1.m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
		}

		if (m_playerTankInfo.playerTank->m_bullet2.m_present)
		{
			DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_bulletBitmaps[static_cast<UINT>(m_playerTankInfo.playerTank->m_bullet2.m_direction)].Get(),
				m_playerTankInfo.playerTank->m_bullet2.m_topLeftCornerPoint.x, m_playerTankInfo.playerTank->m_bullet2.m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
		}
	}
}

void BattleCityMain::DrawExplosion()
{
	__int64 currentFrame = m_timer.CurrentFrame();
	for (auto&p : m_runningInfo.explosionList)
	{
		if (p.isBigExplosion)
		{
			if (currentFrame - p.explosionFrame < 60)
			{
				DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_bulletBigExplosionBitmaps[(currentFrame - p.explosionFrame) / 12].Get(),
					p.explosionPos.x, p.explosionPos.y, m_gameClientLeftX, m_gameClientTopY);
			}
		}
		else
		{
			if (currentFrame - p.explosionFrame < 36)
			{
				DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_bulletBigExplosionBitmaps[(currentFrame - p.explosionFrame) / 12].Get(),
					p.explosionPos.x, p.explosionPos.y, m_gameClientLeftX, m_gameClientTopY);
			}
		}
	}

	auto pbegin = m_runningInfo.explosionList.begin();
	auto pend = m_runningInfo.explosionList.end();

	while (pbegin != pend)
	{
		if (pbegin->isBigExplosion&&currentFrame - pbegin->explosionFrame > 60)
		{
			m_runningInfo.explosionList.erase(pbegin);
			pbegin = m_runningInfo.explosionList.begin();
			pend = m_runningInfo.explosionList.end();
		}
		else
		{
			pbegin++;
		}
	}
}

void BattleCityMain::DrawBase()
{
	if (!m_baseDestroyed)
	{
		DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_baseBitmap.Get(), 192, 384, m_gameClientLeftX, m_gameClientTopY);
	}
	else
	{
		DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_baseDestroyedBitmap.Get(), 192, 384, m_gameClientLeftX, m_gameClientTopY);
	}
}

void BattleCityMain::DrawGameoverMessage()
{
	if (!m_runningInfo.bGameover)
		return;

	__int64 currentFrame = m_timer.CurrentFrame();

	int animationHeight = ((currentFrame <= (m_runningInfo.overFrame + 240)) ?
		((218 - m_clientHeight) * (currentFrame - m_runningInfo.overFrame - 240) / 240  + 218) : 218);
	DrawText(m_pDirect2dContext.Get(), m_pTextFormat.Get(), m_pBrushRed.Get(), L"GAME", 210, animationHeight, m_clientWidth, m_clientHeight);
	DrawText(m_pDirect2dContext.Get(), m_pTextFormat.Get(), m_pBrushRed.Get(), L"OVER", 210, animationHeight + 16 , m_clientWidth, m_clientHeight);
	
	if (currentFrame > m_runningInfo.overFrame + 480)
	{
		m_gameState = GameState::GAME_COUNTING;
	}
}

void BattleCityMain::DrawTerrain(int x, int y, TerrainType type)
{
	switch (type)
	{
	case TerrainType::TERRAIN_WALLBLICK:
	case TerrainType::TERRAIN_WALLSTEEL:
		DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_terrainBitmaps[static_cast<UINT>(type)].Get(), x * 16, y * 16, m_gameClientLeftX, m_gameClientTopY);
		break;
	case TerrainType::TERRAIN_TREES:
		DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_terrainBitmaps[static_cast<UINT>(type)].Get(), x * 16, y * 16, m_gameClientLeftX, m_gameClientTopY);
		break;
	}
}

void BattleCityMain::DrawMap()
{
	for (int i = 0; i < 26; i++)		// 纵坐标
	{
		for (int j = 0; j < 26; j++)	// 横坐标
		{
			switch (m_runningInfo.terrain[i][j])
			{
			case TerrainType::TERRAIN_WALLBLICK:
			case TerrainType::TERRAIN_WALLSTEEL:
			case TerrainType::TERRAIN_TREES:
				DrawTerrain(j, i, m_runningInfo.terrain[i][j]);
				break;
			}
		}
	}
}

void BattleCityMain::DrawInfo()
{
	ID2D1DeviceContext *pContext = m_pDirect2dContext.Get();

	// 显示当前未出现的坦克数量
	for (int i = 0; i < m_enemyTankInfo.enemyTank.size() - m_enemyTankInfo.summonedEnemyTank; i++)
	{
		int x = 465 + 16 * (i % 2);
		int y = 34 + 16 * (i / 2);
		DrawBitmap(pContext, m_enemyNumBitmap.Get(), x, y);
	}

	// 显示剩余生命值
	DrawBitmap(pContext, m_romanOneBitmap.Get(), 468, 256);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushBlack.Get(), L"P", 482, 256, m_clientWidth, m_clientHeight);
	DrawBitmap(pContext, m_playerLivesBitmap.Get(), 465, 272);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushBlack.Get(), to_wstring(m_playerTankInfo.playerLives), 482, 272, m_clientWidth, m_clientHeight);

	// 显示当前关卡
	DrawBitmap(pContext, m_stageFlagBitmap.Get(), 464, 352);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushBlack.Get(), to_wstring(m_stageInfo.stage), 482, 382, m_clientWidth, m_clientHeight);
}

void BattleCityMain::DrawSummoningAnimation()
{
	__int64 currentFrame = m_timer.CurrentFrame();
	for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
	{
		if (currentFrame - m_enemyTankInfo.enemyTank[i]->m_summonedFrame < 120)
		{
			DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_tankLoadingBitmaps[((currentFrame - m_enemyTankInfo.enemyTank[i]->m_summonedFrame) / 10) % 4].Get(),
				m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.x, m_enemyTankInfo.enemyTank[i]->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
		}
		else if (currentFrame - m_enemyTankInfo.enemyTank[i]->m_summonedFrame > 120)
		{
			m_enemyTankInfo.enemyTank[i]->m_invincible = false;
			m_enemyTankInfo.enemyTank[i]->m_movable = true;
			m_enemyTankInfo.enemyTank[i]->m_initing = false;
		}
	}

	if (m_playerTankInfo.playerTank != nullptr && (currentFrame - m_playerTankInfo.playerTank->m_summonedFrame < 120))
	{
		DrawBitmapInGameClient(m_pDirect2dContext.Get(), m_tankLoadingBitmaps[((currentFrame - m_playerTankInfo.playerTank->m_summonedFrame) / 10) % 4].Get(),
			m_playerTankInfo.playerTank->m_topLeftCornerPoint.x, m_playerTankInfo.playerTank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
	}
	else if (m_playerTankInfo.playerTank != nullptr && currentFrame - m_playerTankInfo.playerTank->m_summonedFrame > 120)
	{
		m_playerTankInfo.playerTank->m_invincible = false;
		m_playerTankInfo.playerTank->m_movable = true;
		m_playerTankInfo.playerTank->m_initing = false;
	}
}

void BattleCityMain::DrawTank()
{
	ID2D1DeviceContext *pContext = m_pDirect2dContext.Get();
	__int64 currentFrame = m_timer.CurrentFrame();
	// 敌方坦克绘制
	EnemyTank *tank;
	for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
	{
		tank = m_enemyTankInfo.enemyTank[i];
		int tankGoingAnimation = ((tank->m_isGoing && !m_bPaused) ? (currentFrame % 8 > 4 ? 0 : 1) : 0);
		if (!tank->m_destroyed && !tank->m_initing)
		{
			switch (tank->m_type)
			{
			case EnemyTankType::ARMOR_TANK:
				DrawBitmapInGameClient(pContext,
					m_armorTankBitmaps[(3 - static_cast<ArmorTank*>(tank)->m_life) * 8 + static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
					tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				break;

			case EnemyTankType::FAST_TANK:
				if (!tank->m_haveProp)
				{
					DrawBitmapInGameClient(pContext,
						m_fastTankBitmaps[static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
						tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				}
				else
				{
					DrawBitmapInGameClient(pContext,
						m_fastTankBitmaps[(currentFrame % 40 > 20 ? 0 : 1) * 8 + static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
						tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				}
				break;

			case EnemyTankType::BASIC_TANK:
				if (!tank->m_haveProp)
				{
					DrawBitmapInGameClient(pContext,
						m_basicTankBitmaps[static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
						tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				}
				else
				{
					DrawBitmapInGameClient(pContext,
						m_basicTankBitmaps[(currentFrame % 40 > 20 ? 0 : 1) * 8 + static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
						tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				}
				break;

			case EnemyTankType::POWER_TANK:
				if (!tank->m_haveProp)
				{
					DrawBitmapInGameClient(pContext,
						m_powerTankBitmaps[static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
						tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				}
				else
				{
					DrawBitmapInGameClient(pContext,
						m_powerTankBitmaps[(currentFrame % 40 > 20 ? 0 : 1) * 8 + static_cast<UINT>(tank->m_direction) * 2 + tankGoingAnimation].Get(),
						tank->m_topLeftCornerPoint.x, tank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
				}
				break;
			}
		}
	}

	// 我方坦克绘制
	if (m_playerTankInfo.playerTank != nullptr && m_playerTankInfo.playerLives >= 0 && !m_playerTankInfo.playerTank->m_initing)
	{
		int tankGoingAnimation = (m_playerTankInfo.playerTank->m_isGoing && !m_bPaused ? (currentFrame % 8 > 4 ? 0 : 1) : 0);
		DrawBitmapInGameClient(pContext,
			m_playerTankBitmaps[m_playerTankInfo.playerTank->m_star * 8 + static_cast<UINT>(m_playerTankInfo.playerTank->m_direction) * 2 + tankGoingAnimation].Get(),
			m_playerTankInfo.playerTank->m_topLeftCornerPoint.x, m_playerTankInfo.playerTank->m_topLeftCornerPoint.y, m_gameClientLeftX, m_gameClientTopY);
	}
}

#pragma warning(pop)