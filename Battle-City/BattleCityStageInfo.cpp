#include "stdafx.h"
#include "BattleCityMain.h"
#include "BattleCityObject.h"

void BattleCityMain::LoadMap()
{
	// STAGE 1
	if (m_stageInfo.stage == 1)
	{
		m_runningInfo.terrain[0] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND
		};
		m_runningInfo.terrain[1] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND ,TERRAIN_GROUND
		};
		m_runningInfo.terrain[2] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[3] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[4] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[5] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[6] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[7] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[8] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};

		m_runningInfo.terrain[9] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[10] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[11] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[12] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[13] =
		{
			TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_GROUND, TERRAIN_GROUND,
			TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK,
			TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK
		};
		m_runningInfo.terrain[14] =
		{
			TERRAIN_WALLSTEEL, TERRAIN_WALLSTEEL, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_GROUND, TERRAIN_GROUND,
			TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_WALLBLICK, TERRAIN_WALLBLICK,
			TERRAIN_WALLBLICK, TERRAIN_WALLBLICK, TERRAIN_GROUND, TERRAIN_GROUND, TERRAIN_WALLSTEEL, TERRAIN_WALLSTEEL
		};
		m_runningInfo.terrain[15] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[16] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[17] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[18] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[19] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[20] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[21] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[22] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[23] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[24] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[25] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
	}
	// STAGE 2
	else if (m_stageInfo.stage == 2)
	{
		m_runningInfo.terrain[0] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[1] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[2] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[3] = 
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[4] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[5] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[6] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[7] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[8] =
		{
			TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL
		};
		m_runningInfo.terrain[9] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL
		};
		m_runningInfo.terrain[10] =
		{
			TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[11] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[12] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_TREES,TERRAIN_GROUND,
			TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_TREES,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[13] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[14] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_TREES,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[15] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[16] =
		{
			TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[17] =
		{
			TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[18] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[19] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_WALLSTEEL,TERRAIN_WALLSTEEL,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[20] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[21] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[22] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[23] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[24] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
		m_runningInfo.terrain[25] =
		{
			TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,
			TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_GROUND,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,
			TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_WALLBLICK,TERRAIN_GROUND,TERRAIN_GROUND
		};
	}
}

void BattleCityMain::LoadEnemyTank()
{
	if (m_stageInfo.stage == 1)
	{
		m_enemyTankInfo.enemyTank.resize(20);
		for (int i = 0; i < 18; i++)
		{
			m_enemyTankInfo.enemyTank[i] = new BasicTank;
		}

		m_enemyTankInfo.enemyTank[18] = new FastTank;
		m_enemyTankInfo.enemyTank[19] = new FastTank;
		for (int i = 4; i < m_enemyTankInfo.enemyTank.size(); i += 5)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_type != EnemyTankType::ARMOR_TANK)
			{
				m_enemyTankInfo.enemyTank[i]->m_haveProp = true;
			}
		}
	}
	else if (m_stageInfo.stage == 2)
	{
		m_enemyTankInfo.enemyTank.resize(20);
		m_enemyTankInfo.enemyTank[0] = new ArmorTank;
		m_enemyTankInfo.enemyTank[1] = new ArmorTank;
		m_enemyTankInfo.enemyTank[2] = new FastTank;
		m_enemyTankInfo.enemyTank[3] = new FastTank;
		m_enemyTankInfo.enemyTank[4] = new FastTank;
		m_enemyTankInfo.enemyTank[5] = new FastTank;
		for (int i = 6; i < 20; i++)
		{
			m_enemyTankInfo.enemyTank[i] = new BasicTank;
		}
		for (int i = 4; i < m_enemyTankInfo.enemyTank.size(); i += 5)
		{
			if (m_enemyTankInfo.enemyTank[i]->m_type != EnemyTankType::ARMOR_TANK)
			{
				m_enemyTankInfo.enemyTank[i]->m_haveProp = true;
			}
		}
	}
}

void BattleCityMain::ReleaseEnemyTank()
{
	for (auto &p : m_enemyTankInfo.enemyTank)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}
}
