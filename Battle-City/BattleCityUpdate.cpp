#include "stdafx.h"
#include "D2DException.h"
#include "BattleCityMain.h"
#include "BattleCityObject.h"
#include "resource.h"

void BattleCityMain::UpdateScene()
{
	switch (m_gameState)
	{
	case GameState::GAME_MENU:
		GameMenuUpdate();
		break;

	case GameState::GAME_BEGIN:
		GameStageUpdate();
		break;

	case GameState::GAME_RUNNING:
		GameRunningUpdate();
		break;

	case GameState::GAME_COUNTING:
		GameCountingUpdate();
		break;

	case GameState::GAME_OVER:
		GameOverUpdate();
		break;
	}
}

void BattleCityMain::GameMenuUpdate()
{
	
}

void BattleCityMain::GameStageUpdate()
{
	__int64 currentFrame = m_timer.CurrentFrame();

	if (m_stageInfo.beginFrame == 0)
	{
		PlaySoundFromResource(MAKEINTRESOURCE(IDB_WAV_STAGE_START), SOUND_RESOURCE_TYPE);
		m_stageInfo.stage++;
		m_stageInfo.beginFrame = m_timer.CurrentFrame();
		m_runningInfo.bGameover = false;
		m_runningInfo.overFrame = 0;
		m_enemyTankInfo.presentEnemyTank = 0;
		m_enemyTankInfo.summonedEnemyTank = 0;
		ReleaseEnemyTank();
		LoadMap();
		LoadEnemyTank();
		if (m_stageInfo.stage == 1)
		{
			memset(&m_playerTankInfo, 0, sizeof(PlayerTankInfo));
			m_baseDestroyed = false;
			m_runningInfo.score = 0;
			m_playerTankInfo.playerLives = 3;
		}
	}
}

void BattleCityMain::GameRunningUpdate()
{
	__int64 currentFrame = m_timer.CurrentFrame();

	// 初始坦克召唤
	if ((currentFrame - m_runningInfo.beginFrame) == 2)
	{
		m_playerTankInfo.playerTank = new PlayerTank;
		SummonTank(false);
	}
	
	// 每四秒刷新一只坦克出来
	if ((currentFrame - m_runningInfo.beginFrame) % (4 * m_fps) == 2)
	{
		if (m_enemyTankInfo.presentEnemyTank < 4 && m_enemyTankInfo.summonedEnemyTank < 20)
		{
			SummonTank(true);
		}
	}

	// 设置通关信息
	if (m_enemyTankInfo.presentEnemyTank == 0 && m_enemyTankInfo.summonedEnemyTank == 20 && m_runningInfo.overFrame == 0)
	{
		m_runningInfo.overFrame = currentFrame;
	}

	// 结束游戏判定
	if (m_baseDestroyed && !m_runningInfo.bGameover)
	{
		m_runningInfo.bGameover = true;
		m_runningInfo.overFrame = currentFrame;
		m_playerTankInfo.playerTank->m_movable = false;
	}
	else if (currentFrame - m_runningInfo.overFrame > 360 && m_runningInfo.overFrame != 0)
	{
		m_gameState = GameState::GAME_COUNTING;
		return;
	}

	// 更新玩家坦克信息
	if (m_playerTankInfo.playerTank != nullptr)
	{
		if (KEY_DOWN(VK_UP))
		{
			m_playerTankInfo.playerTank->m_isGoing = true;
			m_playerTankInfo.playerTank->m_direction = Direction::UP;
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_playerTankInfo.playerTank->m_isGoing = true;
			m_playerTankInfo.playerTank->m_direction = Direction::DOWN;
		}
		else if (KEY_DOWN(VK_RIGHT))
		{
			m_playerTankInfo.playerTank->m_isGoing = true;
			m_playerTankInfo.playerTank->m_direction = Direction::RIGHT;
		}
		else if (KEY_DOWN(VK_LEFT))
		{
			m_playerTankInfo.playerTank->m_isGoing = true;
			m_playerTankInfo.playerTank->m_direction = Direction::LEFT;
		}
		else
		{
			m_playerTankInfo.playerTank->m_isGoing = false;
		}

		if (m_playerTankInfo.playerTank->m_bullet1.m_present)
		{
			m_playerTankInfo.playerTank->m_bullet1.GoToNextPoint();
		}
		if (m_playerTankInfo.playerTank->m_bullet2.m_present)
		{
			m_playerTankInfo.playerTank->m_bullet2.GoToNextPoint();
		}

		m_playerTankInfo.playerTank->GoToNextPoint(currentFrame);
	}

	// 更新敌方坦克位置
	for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
	{
		if (!m_enemyTankInfo.enemyTank[i]->m_destroyed)
		{
			m_enemyTankInfo.enemyTank[i]->GoToNextPoint(currentFrame);
		}
	}

	// 更新敌方子弹位置
	for (int i = 0; i < m_enemyTankInfo.summonedEnemyTank; i++)
	{
		if (m_enemyTankInfo.enemyTank[i]->m_bullet.m_present)
		{
			m_enemyTankInfo.enemyTank[i]->m_bullet.GoToNextPoint();
		}
	}

	// 刷新子弹信息
	FreshBullets();
}

void BattleCityMain::GameCountingUpdate()
{
}

void BattleCityMain::GameOverUpdate()
{
	__int64 currentFrame = m_timer.CurrentFrame();
	if (currentFrame - m_overInfo.beginFrame > static_cast<double>(m_fps) * 2.5)
	{
		m_stageInfo.beginFrame = 0;
		m_stageInfo.stage = 0;
		m_runningInfo.explosionList.clear();
		m_runningInfo.bGameover = false;
		m_baseDestroyed = false;
		m_enemyTankInfo.summonedEnemyTank = 0;
		m_enemyTankInfo.presentEnemyTank = 0;
		EnemyTank::s_bornPoint = 1;
		m_menuInfo.beginFrame = currentFrame;
		m_menuInfo.chosenItem = GameMenuInfo::ONE_PLAYER;
		m_menuInfo.animationPlayed = false;
		m_gameState = GameState::GAME_MENU;
	}
}
