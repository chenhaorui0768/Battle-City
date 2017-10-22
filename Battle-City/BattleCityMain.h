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
		}										chosenItem;				// ѡ�еĲ˵�ѡ��
		bool									animationPlayed;		// ���ڲ��Ų˵�����
		__int64									beginFrame;				// ��ʼʱ��֡��
	};

	struct GameStageInfo
	{
		int										stage;					// �ؿ���
		__int64									beginFrame;				// �ؿ���ʼʱ��
	};

	struct GameRunningInfo
	{
		bool									bGameover;				// ��ͣ״̬
		int										score;					// ���÷���
		__int64									beginFrame;				// ��Ϸ��ʼʱ֡��
		__int64									pauseFrame;				// ��Ϸ��ͣʱ֡��
		__int64									overFrame;				// ��Ϸ������ʧ�ܣ�ʱ��֡��
		array<array<TerrainType, 26>, 26>		terrain;				// ������Ϣ��ǰ index Ϊ������
		list<ExplosionInfo>						explosionList;			// ��ͼ�еı�ը��Ϣ
	};

	struct GameOverInfo
	{
		__int64									beginFrame;				// ������Ϸ����ʱ��֡��
	};

	struct EnemyTankInfo
	{
		vector<EnemyTank*>						enemyTank;				// �з�̹���б�
		int										summonedEnemyTank = 1;	// �Ѿ����ֹ���̹����
		int										presentEnemyTank = 0;	// �����ڳ��ϵ�̹����
	};

	struct PlayerTankInfo
	{
		PlayerTank*								playerTank;				// �ҷ�̹���б�
		int										playerLives;			// �ҷ�̹��ʣ������
		// �ƻ���̹���б�
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
	bool		FreshBullets();								// ��ÿһ���ӵ���������ײ״̬
	bool		UpdateBullet(Bullet &bullet);

protected:
	// ���ؼ��ͷ���ͼ��Դ
	bool		LoadingBitmaps();
	bool		ReleaseBitmaps();

	void		LoadMap();
	void		LoadEnemyTank();
	void		ReleaseEnemyTank();

	void		DrawScene()override;		// ����
	void		UpdateScene()override;		// ���»���������

	// ��Ϸ������ƺ���
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

	// ��д����Ϣ������
	LRESULT		OnDestroy()override;
	LRESULT		OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags)override;

	// ��Ⱦ�߳�
	friend void Render(BattleCityMain *gameMain);

protected:

#pragma region D2D��Դ
	// ��ͼ

	// ������ͼ
	array<ComPtr<ID2D1Bitmap1>, TERRAIN_BITMAP_NUM>			m_terrainBitmaps;
	// ������ͼ
	ComPtr<ID2D1Bitmap1>									m_baseBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_baseDestroyedBitmap = nullptr;
	// ̹����ͼ
	array<ComPtr<ID2D1Bitmap1>, ARMOR_TANK_BITMAP_NUM>		m_armorTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, BASIC_TANK_BITMAP_NUM>		m_basicTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, FAST_TANK_BITMAP_NUM>		m_fastTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, POWER_TANK_BITMAP_NUM>		m_powerTankBitmaps;
	array<ComPtr<ID2D1Bitmap1>, PLAYER_TANK_BITMAP_NUM>		m_playerTankBitmaps;
	// ̹�˳���ǰ��������ͼ
	array<ComPtr<ID2D1Bitmap1>, 4>							m_tankLoadingBitmaps;
	// ̹���ӵ���ͼ
	array<ComPtr<ID2D1Bitmap1>, 4>							m_bulletBitmaps;
	// �ӵ���ը��ͼ
	array<ComPtr<ID2D1Bitmap1>, 3>							m_bulletExplosionBitmaps;
	array<ComPtr<ID2D1Bitmap1>, 5>							m_bulletBigExplosionBitmaps;
	// ��Ϸ�˵�������ͼ
	ComPtr<ID2D1Bitmap1>									m_battleCityBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_namcotBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_copyrightBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_romanOneWhiteBitmap = nullptr;
	// ��Ϸʱ��Ϣ����ͼ
	ComPtr<ID2D1Bitmap1>									m_stageFlagBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_romanOneBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_playerLivesBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_enemyNumBitmap = nullptr;
	// ��Ϸ����������ͼ
	ComPtr<ID2D1Bitmap1>									m_gameoverBitmap = nullptr;
	// ��Ϸ���������ͼ
	ComPtr<ID2D1Bitmap1>									m_romanOneRedBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_whiteLineBitmap = nullptr;
	ComPtr<ID2D1Bitmap1>									m_arrowBitmap = nullptr;

	// ����
	ComPtr<IDWriteTextFormat2>								m_pTextFormat = nullptr;

	// ��ˢ
	ComPtr<ID2D1SolidColorBrush>							m_pBrushRed = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushWhite = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushBlack = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushGray = nullptr;
	ComPtr<ID2D1SolidColorBrush>							m_pBrushOrange = nullptr;
#pragma endregion

#pragma region ��Ϸ����ʱ��Ϣ
	GameState												m_gameState = GameState::GAME_INIT;	// ��Ϸ״̬
	GameStageInfo											m_stageInfo;						// ��Ϸ�ؿ���Ϣ
	GameMenuInfo											m_menuInfo;							// ��Ϸ�˵���Ϣ
	GameRunningInfo											m_runningInfo;						// ��Ϸ����ʱ����Ϣ
	GameOverInfo											m_overInfo;							// ��Ϸ������Ϣ

	EnemyTankInfo											m_enemyTankInfo;					// �з�̹����Ϣ
	PlayerTankInfo											m_playerTankInfo;					// �ҷ�̹����Ϣ

	static const int										m_gameClientLeftX = 32;				// ��Ϸ�����ϽǺ�����
	static const int										m_gameClientWidth = 13 * 32;		// ��Ϸ�����
	static const int										m_gameClientTopY = 16;				// ��Ϸ�����Ͻ�������
	static const int										m_gameClientHeight = 13 * 32;		// ��Ϸ���߶�

	bool													m_baseDestroyed = false;			// ���ر��ݻ٣�
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
