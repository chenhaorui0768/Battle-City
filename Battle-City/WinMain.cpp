#include "stdafx.h"
#include "D2DException.h"
#include "BattleCityMain.h"

// 程序入口点
int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{
	using namespace D2DAPP;
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	
	int ret = 1;

	try
	{
		ThrowIfFailed(CoInitialize(NULL));
		BattleCityMain gameMain;
		if (gameMain.Init(hInstance))
		{
			ret = gameMain.Run();
		}
		gameMain.Release();
		CoUninitialize();
	}
	catch (D2DException & err)
	{
		err.ShowError();
		return 1;
	}

	return ret;
}