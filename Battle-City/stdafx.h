#pragma once

// Windows ͷ�ļ�
#include <Windows.h>

// COM ����ͷ�ļ�
#include <comdef.h>
#include <wincodec.h>

// WRL ͷ�ļ�
#include <wrl.h>

// DirectX ͷ�ļ�
#include <d3d11_4.h>
#include <d2d1_3.h>
#include <dwrite_3.h>

// C++ ͷ�ļ�
#include <string>
#include <array>
#include <list>
#include <vector>
#include <thread>

// ��Ϸʱ��
#include "GameTimer.h"

// ���ӿ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dwrite.lib")

// ��������ռ�
using namespace D2D1;
using Microsoft::WRL::ComPtr;
using std::wstring;
using std::to_wstring;
using std::array;
using std::list;
using std::vector;
using std::thread;

// ͨ�õĺ�
#define ASSERT_OR_THROW(condition)	ThrowIfFailed(condition ? S_OK : E_FAIL)
#define KEY_DOWN(vk_code)			((GetAsyncKeyState(vk_code) & 0x8000) ? true : false)
#define KEY_UP(vk_code)				((GetAsyncKeyState(vk_code) & 0x8000) ? false : true)
