#pragma once

// Windows 头文件
#include <Windows.h>

// COM 公共头文件
#include <comdef.h>
#include <wincodec.h>

// WRL 头文件
#include <wrl.h>

// DirectX 头文件
#include <d3d11_4.h>
#include <d2d1_3.h>
#include <dwrite_3.h>

// C++ 头文件
#include <string>
#include <array>
#include <list>
#include <vector>
#include <thread>

// 游戏时钟
#include "GameTimer.h"

// 链接库
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dwrite.lib")

// 相关命名空间
using namespace D2D1;
using Microsoft::WRL::ComPtr;
using std::wstring;
using std::to_wstring;
using std::array;
using std::list;
using std::vector;
using std::thread;

// 通用的宏
#define ASSERT_OR_THROW(condition)	ThrowIfFailed(condition ? S_OK : E_FAIL)
#define KEY_DOWN(vk_code)			((GetAsyncKeyState(vk_code) & 0x8000) ? true : false)
#define KEY_UP(vk_code)				((GetAsyncKeyState(vk_code) & 0x8000) ? false : true)
