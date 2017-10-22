#ifndef BATTLE_CITY_MAIN_H
#define BATTLE_CITY_MAIN_H

#include "stdafx.h"
#include "D2DApp.h"
#include "D2DException.h"
#include "BattleCityObject.h"

enum class GameState
{
	GAME_INIT,
	GAME_MENU,
	GAME_BEGIN,
	GAME_RUNNING,
	GAME_PAUSE,
	GAME_OVER,
	GAME_COUNTING,
	GAME_CLOSING
};

struct ExplosionInfo
{
	bool			isBigExplosion;
	__int64			explosionFrame;
	D2D1_POINT_2F	explosionPos;
};

class BattleCityMain :public D2DAPP::D2DApp
{
	struct GameMenuInfo
	{
		enum
		{
			ONE_PLAYER
		}										chosenItem;				// 选中的菜单选项
		bool									animationPlayed;		// 正在播放菜单动画
		__int64									beginFrame;				// 开始时的帧数
	};

	struct GameStageInfo
	{
		int										stage;					// 关卡数
		__int64									beginFrame;				// 关卡开始时间
	};

	struct GameRunningInfo
	{
		bool									bGameover;				// 暂停状态
		int										score;					// 所得分数
		__int64									beginFrame;				// 游戏开始时帧数
		__int64									pauseFrame;				// 游戏暂停时帧数
		__int64									overFrame;				// 游戏结束（失败）时的帧数
		array<array<TerrainType, 26>, 26>		terrain;				// 地形信息，前 index 为纵坐标
		list<ExplosionInfo>						explosionList;			// 地图中的爆炸信息
	};

	struct GameOverInfo
	{
		__int64									beginFrame;				// 播放游戏结束时的帧数
	};

	struct EnemyTankInfo
	{
		vector<EnemyTank*>						enemyTank;				// 敌方坦克列表
		int										summonedEnemyTank = 1;	// 已经出现过的坦克数
		int										presentEnemyTank = 0;	// 存在于场上的坦克数
	};

	struct PlayerTankInfo
	{
		PlayerTank*								playerTank;				// 我方坦克列表
		int										playerLives;			// 我方坦克剩余生命
		// 破坏的坦克列表
		int										destroyedBasicTank;
		int										destroyedFastTank;
		int										destroyedArmorTank;
		int										destroyedPowerTank;
	};

public:
	BattleCityMain();

	bool		Init(HINSTANCE hInstance)override;
	bool		Release()override;

	bool		IsBlankPoint(const Tank *tank, Direction direction, const D2D1_POINT_2F &point);
	bool		FreshBullets();								// 对每一颗子弹，检验碰撞状态
	bool		UpdateBullet(Bullet &bullet);

protected:
	// 加载及释放贴图资源
	bool		LoadingBitmaps();
	bool		ReleaseBitmaps();

	void		LoadMap();
	void		LoadEnemyTank();
	void		ReleaseEnemyTank();

	void		DrawScene()override;		// 画画
	void		UpdateScene()override;		// 更新画画的内容

	// 游戏界面绘制函数
	void		GameMenuScene();
	void		GameStageScene();
	void		GameRunningScene();
	void		GamePausedScene();
	void		GameCountingScene();
	void		GameOverScene();

	void		GameMenuUpdate();
	void		GameStageUpdate();
	void		GameRunningUpdate();
	void		GameCountingUpdate();
	void		GameOverUpdate();

	void		DrawTerrain(int x, int y, TerrainType type);
	void		DrawMap();
	void		DrawInfo();
	void		DrawSummoningAnimation();
	void		DrawTank();
	void		DrawBullet();
	void		DrawExplosion();
	void		DrawBase();
	void		DrawGameoverMessage();

	void		SummonTank(bool isEnemy);

	// 重写的消息处理函数
	LRESULT		OnDestroy()override;
	LRESULT		OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags)override;

	// 渲染线程
	friend void Render(BattleCityMain *gameMain);

protected:

#pragma region D2D资源
	// 贴图

	// 地形贴图
	array<ComPtr<ID2D1Bitmap1>, TERRAIN_BITMAP_NUM>			m_terrainBitmaps;
	// 基地贴图
	ComPtr<ID2D1Bitmap1>									m_baseBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_baseDestroyedBitmap = nullptr;
	// 坦克贴图
	array<ComPtr<ID2D1Bitmap1>, ARMOR_TANK_BITMAP_NUM>		m_armorTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, BASIC_TANK_BITMAP_NUM>		m_basicTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, FAST_TANK_BITMAP_NUM>		m_fastTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, POWER_TANK_BITMAP_NUM>		m_powerTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, PLAYER_TANK_BITMAP_NUM>		m_playerTankBitmaps;
	// 坦克出现前的星星贴图
	array<ComPtr<ID2D1Bitmap1>, 4>							m_tankLoadingBitmaps;
	// 坦克子弹贴图
	array<ComPtr<ID2D1Bitmap1>, 4>							m_bulletBitmaps;
	// 子弹爆炸贴图
	array<ComPtr<ID2D1Bitmap1>, 3>							m_bulletExplosionBitmaps;
	array<ComPtr<ID2D1Bitmap1>, 5>							m_bulletBigExplosionBitmaps;
	// 游戏菜单界面贴图
	ComPtr<ID2D1Bitmap1>									m_battleCityBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_namcotBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_copyrightBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_romanOneWhiteBitmap = nullptr;
	// 游戏时信息栏贴图
	ComPtr<ID2D1Bitmap1>									m_stageFlagBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_romanOneBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_playerLivesBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_enemyNumBitmap = nullptr;
	// 游戏结束界面贴图
	ComPtr<ID2D1Bitmap1>									m_gameoverBitmap = nullptr;
	// 游戏清算界面贴图
	ComPtr<ID2D1Bitmap1>									m_romanOneRedBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_whiteLineBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_arrowBitmap = nullptr;

	// 字体
	ComPtr<IDWriteTextFormat2>								m_pTextFormat = nullptr;

	// 画刷
	ComPtr<ID2D1SolidColorBrush>							m_pBrushRed = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushWhite = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushBlack = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushGray = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushOrange = nullptr;
#pragma endregion

#pragma region 游戏运行时信息
	GameState												m_gameState = GameState::GAME_INIT;	// 游戏状态
	GameStageInfo											m_stageInfo;						// 游戏关卡信息
	GameMenuInfo											m_menuInfo;							// 游戏菜单信息
	GameRunningInfo											m_runningInfo;						// 游戏运行时的信息
	GameOverInfo											m_overInfo;							// 游戏结束信息

	EnemyTankInfo											m_enemyTankInfo;					// 敌方坦克信息
	PlayerTankInfo											m_playerTankInfo;					// 我方坦克信息

	static const int										m_gameClientLeftX = 32;				// 游戏区左上角横坐标
	static const int										m_gameClientWidth = 13 * 32;		// 游戏区宽度
	static const int										m_gameClientTopY = 16;				// 游戏区左上角纵坐标
	static const int										m_gameClientHeight = 13 * 32;		// 游戏区高度

	bool													m_baseDestroyed = false;			// 基地被摧毁？
#pragma endregion

};

inline UINT LeftLineMakeImageCenter(UINT imageWidth, UINT clientWidth)
{
	return (clientWidth - imageWidth) / 2;
}

inline void DrawBitmapInGameClient(ID2D1DeviceContext* context, ID2D1Bitmap1 *bitmap, float left, float top, float clientLeft, float clientTop)
{
	DrawBitmap(context, bitmap, left + clientLeft, top + clientTop);
}

inline bool floatEqual(float f1, float f2)
{
	return (abs(f1 - f2) < 3.5);
}

template<size_t i>
inline void ReleaseBitmapsInArray(array<ComPtr<ID2D1Bitmap1>, i> &arr)
{
	for (auto &p : arr)
	{
		p.Reset();
	}
}

inline bool IntersectionNotEmpty(float section1left, float section1right, float section2left, float section2right)
{
	ASSERT_OR_THROW(section1left < section1right);
	ASSERT_OR_THROW(section2left < section2right);

	if (section1left < section2left && section2right < section1right)
		return true;
	if (section2left < section1left && section1right < section2right)
		return true;
	if (section1left < section2left && section2left < section1right)
		return true;	
	if (section2left < section1left && section1left < section2right)
		return true;

	return false;
}

#endif
