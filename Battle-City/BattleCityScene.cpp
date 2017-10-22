#include "stdafx.h"
#include "D2DException.h"
#include "BattleCityMain.h"
#include "BattleCityObject.h"
#include "resource.h"

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

void BattleCityMain::DrawScene()
{
	if (m_pDirect2dContext != nullptr)
	{
		// 通过调用呈现器目标的 BeginDraw 方法启动绘制
		// 将呈现器目标的转换设置为单位矩阵，并清除窗口
		m_pDirect2dContext->BeginDraw();
		m_pDirect2dContext->SetTransform(D2D1::Matrix3x2F::Identity());

		switch (m_gameState)
		{
		case GameState::GAME_INIT:
			m_pDirect2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
			break;

		case GameState::GAME_MENU:
			GameMenuScene();
			break;

		case GameState::GAME_BEGIN:
			GameStageScene();
			break;

		case GameState::GAME_RUNNING:
			GameRunningScene();
			break;

		case GameState::GAME_PAUSE:
			GamePausedScene();
			break;

		case GameState::GAME_COUNTING:
			GameCountingScene();
			break;

		case GameState::GAME_OVER:
			GameOverScene();
			break;
		}

		// 调用呈现器目标的 EndDraw 方法
		// EndDraw 方法会返回 HRESULT，以指示绘制操作是否成功
		ThrowIfFailed(m_pDirect2dContext->EndDraw());

		// 交换链交换前后缓冲
		ThrowIfFailed(m_pdxgiSwapChain->Present(0, 0));
	}
}

void BattleCityMain::GameMenuScene()
{
	__int64 currentFrame = m_timer.CurrentFrame() - m_menuInfo.beginFrame;

	UINT topHeight = 0;
	UINT imageLeftWidth = 0;

	// 5 秒钟加载动画
	if (!m_menuInfo.animationPlayed && currentFrame <= m_fps * 5)
	{
		topHeight = -static_cast<double>(currentFrame) / (m_fps * 5) * m_clientHeight + m_clientHeight;
	}
	else if (!m_menuInfo.animationPlayed)
	{
		m_menuInfo.animationPlayed = true;
	}

	// 以黑色清屏
	m_pDirect2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	// 绘制分数栏
	ID2D1DeviceContext5 *pContext = m_pDirect2dContext.Get();

	DrawBitmap(pContext, m_romanOneWhiteBitmap.Get(), 36, 32 + topHeight);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushWhite.Get(), L"-    00", 50, 32 + topHeight, m_clientWidth, m_clientHeight);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushWhite.Get(), L"HI- 20000", 178, 32 + topHeight, m_clientWidth, m_clientHeight);

	// 绘制"Battle City"
	DrawBitmap(pContext, m_battleCityBitmap.Get(), 56, 80 + topHeight);

	// 绘制菜单信息
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushWhite.Get(), L"1 PLAYER", 178, 254 + topHeight, m_clientWidth, m_clientHeight);

	// 绘制光标
	if (m_menuInfo.animationPlayed)
	{
		ID2D1Bitmap1 *cursor = m_playerTankBitmaps[(currentFrame % 8 < 4 ? 0 : 1)].Get();
		UINT cursorHeight = (m_menuInfo.chosenItem == GameMenuInfo::ONE_PLAYER ? 254 : 286) - 8;
		DrawBitmap(pContext, cursor, 128, cursorHeight);
	}

	// 绘制版权信息
	DrawBitmap(pContext, m_namcotBitmap.Get(), 176, 352 + topHeight);
	DrawBitmap(pContext, m_copyrightBitmap.Get(), 64, 384 + topHeight);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushWhite.Get(), L"1980 1985 NAMCO LTD.", 98, 384 + topHeight, m_clientWidth, m_clientHeight);
	DrawText(pContext, m_pTextFormat.Get(), m_pBrushWhite.Get(), L"ALL RIGHTS RESERVED", 98, 414 + topHeight, m_clientWidth, m_clientHeight);
}

void BattleCityMain::GameStageScene()
{
	__int64 currentFrame = m_timer.CurrentFrame() - m_stageInfo.beginFrame;

	UINT animationHeightUp = 0.5 * static_cast<double>(m_clientHeight);
	UINT animationHeightDown = 0.5 * static_cast<double>(m_clientHeight);

	// 实现动画
	if (currentFrame <= 0.3 * static_cast<double>(m_fps))
	{
		m_pDirect2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		animationHeightUp = m_clientHeight * currentFrame / (m_fps * 0.6);
		animationHeightDown = m_clientHeight - m_clientHeight * currentFrame / (m_fps * 0.6);
	}
	else if (currentFrame <= 2.0 * static_cast<double>(m_fps) && currentFrame >= 1.7 * static_cast<double>(m_fps))
	{
		GameRunningScene();
		animationHeightUp = m_clientHeight * 3.333 - m_clientHeight * currentFrame / (m_fps * 0.6);
		animationHeightDown = m_clientHeight * currentFrame / (m_fps * 0.6) - m_clientHeight * 2.333;
	}
	else if (currentFrame >= 2.0 * static_cast<double>(m_fps))
	{
		m_runningInfo.beginFrame = m_timer.CurrentFrame();
		m_gameState = GameState::GAME_RUNNING;
		GameRunningScene();
		return;
	}
	m_pDirect2dContext->FillRectangle(D2D1::RectF(0.0f, 0.0f, m_clientWidth, animationHeightUp), m_pBrushGray.Get());
	m_pDirect2dContext->FillRectangle(D2D1::RectF(0.0, animationHeightDown, m_clientWidth, m_clientHeight), m_pBrushGray.Get());

	if (currentFrame <= 1.7 * static_cast<double>(m_fps))
	{
		wstring message = L"STAGE " + to_wstring(m_stageInfo.stage);
		DrawText(m_pDirect2dContext.Get(), m_pTextFormat.Get(), m_pBrushBlack.Get(), message, 195, 206, m_clientWidth, m_clientHeight);
	}
}

void BattleCityMain::GameRunningScene()
{
	__int64 currentFrame = m_timer.CurrentFrame();

	m_pDirect2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
	m_pDirect2dContext->FillRectangle(
		D2D1::RectF(m_gameClientLeftX, m_gameClientTopY, m_gameClientLeftX + 16 * 26, m_gameClientTopY + 16 * 26),
		m_pBrushBlack.Get()
	);
	DrawInfo();
	DrawBase();
	DrawTank();
	DrawSummoningAnimation();
	DrawBullet();
	DrawMap();
	DrawExplosion();
	DrawGameoverMessage();
}

void BattleCityMain::GamePausedScene()
{
	__int64 currentFrame = m_timer.CurrentFrame() - m_runningInfo.pauseFrame;
	GameRunningScene();
	if (currentFrame % 60 < 30)
	{
		DrawText(m_pDirect2dContext.Get(), m_pTextFormat.Get(), m_pBrushRed.Get(),
			L"PAUSE", 202, 226, m_clientWidth, m_clientHeight);
	}
}

void BattleCityMain::GameCountingScene()
{
	auto context = m_pDirect2dContext.Get();
	auto format = m_pTextFormat.Get();
	__int64 currentFrame = m_timer.CurrentFrame();

	// 以黑色清屏
	m_pDirect2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	DrawText(context, format, m_pBrushOrange.Get(), L"20000", 306, 32, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), L"STAGE  " + to_wstring(m_stageInfo.stage), 194, 78 - 14, m_clientWidth, m_clientHeight);
	DrawBitmap(context, m_romanOneRedBitmap.Get(), 52, 96);
	DrawText(context, format, m_pBrushRed.Get(), L"-PLAYER", 66, 110 - 14, m_clientWidth, m_clientHeight);

	m_runningInfo.score = m_playerTankInfo.destroyedArmorTank * 500 + m_playerTankInfo.destroyedBasicTank * 100 + m_playerTankInfo.destroyedFastTank * 200 + m_playerTankInfo.destroyedPowerTank * 200;
	DrawText(context, format, m_pBrushOrange.Get(), to_wstring(m_runningInfo.score), 100, 142 - 14, m_clientWidth, m_clientHeight);

	DrawText(context, format, m_pBrushWhite.Get(), L"PTS", 130, 190 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedBasicTank * 100), 34, 190 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedBasicTank), 190, 190 - 14, m_clientWidth, m_clientHeight);
	DrawBitmap(context, m_basicTankBitmaps[4].Get(), 241, 169);
	DrawBitmap(context, m_arrowBitmap.Get(), 226, 176);

	DrawText(context, format, m_pBrushWhite.Get(), L"PTS", 130, 238 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedFastTank * 200), 34, 238 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedFastTank), 190, 238 - 14, m_clientWidth, m_clientHeight);
	DrawBitmap(context, m_fastTankBitmaps[4].Get(), 241, 217);
	DrawBitmap(context, m_arrowBitmap.Get(), 226, 224);

	DrawText(context, format, m_pBrushWhite.Get(), L"PTS", 130, 286 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedPowerTank * 200), 34, 286 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedPowerTank), 190, 286 - 14, m_clientWidth, m_clientHeight);
	DrawBitmap(context, m_powerTankBitmaps[4].Get(), 241, 265);
	DrawBitmap(context, m_arrowBitmap.Get(), 226, 272);

	DrawText(context, format, m_pBrushWhite.Get(), L"PTS", 130, 334 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedArmorTank * 500), 34, 334 - 14, m_clientWidth, m_clientHeight);
	DrawText(context, format, m_pBrushWhite.Get(), to_wstring(m_playerTankInfo.destroyedArmorTank), 190, 334 - 14, m_clientWidth, m_clientHeight);
	DrawBitmap(context, m_armorTankBitmaps[28].Get(), 241, 313);
	DrawBitmap(context, m_arrowBitmap.Get(), 226, 320);

	DrawBitmap(context, m_whiteLineBitmap.Get(), 192, 346);
	DrawText(context, format, m_pBrushWhite.Get(), L"TOTAL" + to_wstring(m_runningInfo.score), 110, 366 - 14, m_clientWidth, m_clientHeight);

	if (currentFrame - m_runningInfo.overFrame >= 1200)
	{
		if (m_runningInfo.bGameover)
		{
			m_overInfo.beginFrame = currentFrame;
			m_gameState = GameState::GAME_OVER;
		}
		else
		{
			m_stageInfo.beginFrame = 0;
			m_gameState = GameState::GAME_BEGIN;
		}
	}
}

void BattleCityMain::GameOverScene()
{
	__int64 currentFrame = m_timer.CurrentFrame() - m_overInfo.beginFrame;

	// 以黑色清屏
	m_pDirect2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	// 播放 gameover 音乐
	if (currentFrame == 1)
	{
		delete m_playerTankInfo.playerTank;
		m_playerTankInfo.playerTank = nullptr;
		ReleaseEnemyTank();
		PlaySoundFromResource(MAKEINTRESOURCE(IDB_WAV_GAMEOVER), SOUND_RESOURCE_TYPE);
	}

	// 显示 2.5 秒钟"GAME OVER"，后返回菜单界面
	if (currentFrame <= static_cast<double>(m_fps) * 2.5)
	{
		DrawBitmap(m_pDirect2dContext.Get(), m_gameoverBitmap.Get(), 128, 128);
	}
}

#pragma warning(pop)