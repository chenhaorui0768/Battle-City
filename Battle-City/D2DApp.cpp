#include "stdafx.h"
#include "D2DApp.h"
#include "D2DException.h"

namespace D2DAPP
{
	D2DApp *D2DApp::m_spApp = nullptr;

	LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return D2DApp::GetApp()->MainWndProc(hWnd, uMsg, wParam, lParam);
	}

	D2DApp::D2DApp()
	{
		// 设置窗口类
		m_wndClass.cbSize = sizeof(WNDCLASSEX);
		m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
		m_wndClass.lpfnWndProc = D2DAPP::MainWndProc;
		m_wndClass.cbClsExtra = 0;
		m_wndClass.cbWndExtra = 0;
		m_wndClass.hInstance = m_hInstance;
		m_wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		m_wndClass.hIconSm = nullptr;
		m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
		m_wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_wndClass.lpszMenuName = 0;
		m_wndClass.lpszClassName = L"MainWnd";

		// 设置 CreateStruct
		m_createStruct.dwExStyle = 0;
		m_createStruct.lpszClass = L"MainWnd";
		m_createStruct.lpszName = m_windowCaption.c_str();
		m_createStruct.style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
		m_createStruct.x = CW_USEDEFAULT;
		m_createStruct.y = CW_USEDEFAULT;
		m_createStruct.cx = m_clientWidth;
		m_createStruct.cy = m_clientHeight;
		m_createStruct.hwndParent = nullptr;
		m_createStruct.hMenu = nullptr;
		m_createStruct.hInstance = m_hInstance;
		m_createStruct.lpCreateParams = nullptr;
	}

	bool D2DApp::Init(HINSTANCE hInstance)
	{
		m_spApp = this;
		m_hInstance = hInstance;

		if (InitMainWindow() && InitDirect2D())
		{
			// 显示并刷新窗口（发送 WM_PAINT）
			ShowWindow(m_hWnd, SW_SHOW);
			UpdateWindow(m_hWnd);

			return true;
		}
		return false;
	}

	bool D2DApp::InitDirect2D()
	{
		CreateDeviceIndependentResources();
		CreateDeviceResources();

		return true;
	}

	bool D2DApp::Release()
	{
		DiscardDeviceResources();
		m_pDirect2dFactory.Reset();
		m_pWICImagingFactory.Reset();
		m_pDWriteFactory.Reset();
		return true;
	}

	int D2DApp::Run()
	{
		MSG msg = {};
		m_timer.Reset();

		while (GetMessage(&msg,nullptr,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}

	bool D2DApp::InitMainWindow()
	{
		// 注册窗口类
		if (!RegisterClassEx(&m_wndClass))
		{
			MessageBox(0, L"RegisterClass Failed.", 0, 0);
			return false;
		}

		// 设置窗口大小
		RECT R = { 0, 0, m_clientWidth, m_clientHeight };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);

		// 创建窗口
		m_hWnd = CreateWindowEx(
			m_createStruct.dwExStyle,
			m_createStruct.lpszClass,
			m_createStruct.lpszName,
			m_createStruct.style,
			m_createStruct.x,
			m_createStruct.y,
			m_createStruct.cx,
			m_createStruct.cy,
			m_createStruct.hwndParent,
			m_createStruct.hMenu,
			m_createStruct.hInstance,
			m_createStruct.lpCreateParams);

		if (!m_hWnd)
		{
			MessageBox(0, L"CreateWindow Failed.", 0, 0);
			return false;
		}

		return true;
	}

	D2DApp * D2DApp::GetApp()
	{
		return m_spApp;
	}

	int D2DApp::GetFps()
	{
		return m_fps;
	}

	LRESULT D2DApp::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		m_bHandled = true;
		return 0;
	}

	LRESULT D2DApp::OnPaint()
	{
		return 0;
	}

	LRESULT D2DApp::OnSize(UINT nType, int windowWidth, int windowHeight)
	{
		if (nType != SIZE_MINIMIZED)
		{
			m_clientWidth = windowWidth;
			m_clientHeight = windowHeight;
			CreateWindowSizeResources();
			m_bHandled = true;
		}
		return 0;
	}

	LRESULT D2DApp::OnMoving(RECT * rect)
	{
		return 0;
	}

	LRESULT D2DApp::OnMove(int x, int y)
	{
		return 0;
	}

	LRESULT D2DApp::OnDestroy()
	{
		PostQuitMessage(0);
		m_bHandled = true;
		return 0;
	}

	LRESULT D2DApp::OnMouseDown(UINT btnState, int x, int y)
	{
		return 0;
	}

	LRESULT D2DApp::OnMouseUp(UINT btnState, int x, int y)
	{
		return 0;
	}

	LRESULT D2DApp::OnMouseMove(UINT btnState, int x, int y)
	{
		return 0;
	}

	LRESULT D2DApp::OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		return 0;
	}

	LRESULT D2DApp::OnKeyup(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		return 0;
	}

	LRESULT D2DApp::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		m_bHandled = false;
		LRESULT ret;

		switch (uMsg)
		{
		case WM_CREATE:
			ret = OnCreate(reinterpret_cast<LPCREATESTRUCT>(lParam));
			break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			ret = OnMouseDown(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
			ret = OnMouseUp(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_MOUSEMOVE:
			ret = OnMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_KEYDOWN:
			ret = OnKeydown(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_KEYUP:
			ret = OnKeyup(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_PAINT:
			ret = OnPaint();
			break;

		case WM_SIZE:
			ret = OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_DESTROY:
			ret = OnDestroy();
			break;

		case WM_MOVING:
			ret = OnMoving(reinterpret_cast<RECT*>(lParam));
			break;

		case WM_MOVE:
			ret = OnMove(LOWORD(lParam), HIWORD(lParam));
			break;
		}

		if (!m_bHandled)
		{
			ret = DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return ret;
	}

	void D2DApp::CreateDeviceIndependentResources()
	{
		// 创建 Direct2D 工厂
		ThrowIfFailed(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&m_pDirect2dFactory)));
		// 创建 WIC 工厂
		ThrowIfFailed(CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICImagingFactory)));
		// 创建 DirectWrite 工厂
		ThrowIfFailed(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown**>(m_pDWriteFactory.GetAddressOf())));
	}

	void D2DApp::CreateDeviceResources()
	{
		// 设置创建 D3D 设备时的 flag（BGRA 支持和调试层）
		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 创建 Direct3D 设备及其上下文
		ComPtr<ID3D11Device> pDirect3dDevice = nullptr;
		ComPtr<ID3D11DeviceContext> pDirect3dContext = nullptr;
		{
			// 创建 Direct3D 11 设备（基于硬件）
			HRESULT hr = D3D11CreateDevice(nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				flags,
				nullptr,
				0,
				D3D11_SDK_VERSION,
				&pDirect3dDevice,
				nullptr,
				&pDirect3dContext);

			// 若创建失败，则基于 WARP 创建设备
			if (FAILED(hr))
			{
				ThrowIfFailed(D3D11CreateDevice(nullptr,
					D3D_DRIVER_TYPE_WARP,
					nullptr,
					flags,
					nullptr,
					0,
					D3D11_SDK_VERSION,
					&pDirect3dDevice,
					nullptr,
					nullptr));
			}

			// 取得接口为 11.5 版本的设备和上下文
			ThrowIfFailed(pDirect3dDevice.As(&m_pDirect3dDevice));
			ThrowIfFailed(pDirect3dContext.As(&m_pDirect3dContext));
		}
		
		// 创建 DXGI 设备
		ComPtr<IDXGIDevice4> pdxgiDevice = nullptr;
		ThrowIfFailed(m_pDirect3dDevice.As(&pdxgiDevice));

		// 创建 Direct2D 设备
		ComPtr<ID2D1Device> pDirect2dDevice = nullptr;
		ThrowIfFailed(m_pDirect2dFactory->CreateDevice(pdxgiDevice.Get(), &pDirect2dDevice));
		ThrowIfFailed(pDirect2dDevice.As(&m_pDirect2dDevice));

		// 创建 Direct2D 设备上下文
		ThrowIfFailed(m_pDirect2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_pDirect2dContext));

		// 创建窗口大小相关资源
		CreateWindowSizeResources();
	}

	void D2DApp::CreateWindowSizeResources()
	{
		ComPtr<IDXGIDevice4> pdxgiDevice = nullptr;
		ComPtr<IDXGIAdapter> pdxgiAdapter = nullptr;
		ComPtr<IDXGIFactory5> pdxgiFactory = nullptr;
		ComPtr<IDXGISwapChain1> pdxgiSwapChain = nullptr;
		ComPtr<IDXGISurface2> pdxgiSurface = nullptr;

		// 清理先前的呈现器资源
		m_pDirect2dContext->SetTarget(nullptr);
		m_pDirect2dBitmap.Reset();
		m_pDirect3dContext->Flush();

		// 若交换链已存在，则刷新交换链缓冲区
		if (m_pdxgiSwapChain != nullptr)
		{
			ThrowIfFailed(m_pdxgiSwapChain->ResizeBuffers(2,	// 交换链中的缓冲数
				m_clientWidth,									// 宽度
				m_clientHeight,									// 高度
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0));
		}
		// 不存在？创建交换链
		else
		{
			// 交换链描述符
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
			swapChainDesc.Width = m_clientWidth;							// 宽度
			swapChainDesc.Height = m_clientHeight;							// 高度
			swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// 像素格式
			swapChainDesc.Stereo = false;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 2;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			swapChainDesc.Flags = 0;
			swapChainDesc.Scaling = DXGI_SCALING_NONE;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

			// 获取 DXGI 设备
			ThrowIfFailed(m_pDirect3dDevice.As(&pdxgiDevice));

			// 获取 DXGI 适配器
			ThrowIfFailed(pdxgiDevice->GetAdapter(&pdxgiAdapter));

			// 获取 DXGI 工厂
			ThrowIfFailed(pdxgiAdapter->GetParent(IID_PPV_ARGS(&pdxgiFactory)));

			// 创建交换链
			ThrowIfFailed(pdxgiFactory->CreateSwapChainForHwnd(
				m_pDirect3dDevice.Get(),
				m_hWnd,
				&swapChainDesc,
				nullptr,
				nullptr,
				&pdxgiSwapChain));
			pdxgiSwapChain.As(&m_pdxgiSwapChain);

			// 设置 DXGI 队列中最高一帧
			ThrowIfFailed(pdxgiDevice->SetMaximumFrameLatency(1));
		}

		// 设置屏幕方向
		ThrowIfFailed(m_pdxgiSwapChain->SetRotation(DXGI_MODE_ROTATION_IDENTITY));

		// 获取 DXGI 表面
		ThrowIfFailed(m_pdxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&pdxgiSurface)));

		// 创建位图
		D2D1_BITMAP_PROPERTIES1 bitmapProperties = BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96.0f,
			96.0f);

		ThrowIfFailed(m_pDirect2dContext->CreateBitmapFromDxgiSurface(
			pdxgiSurface.Get(),
			bitmapProperties,
			&m_pDirect2dBitmap));

		// 设置渲染目标
		m_pDirect2dContext->SetTarget(m_pDirect2dBitmap.Get());
	}

	void D2DApp::DiscardDeviceResources()
	{
		// 按创建的相反顺序释放
		m_pDirect2dBitmap.Reset();
		m_pdxgiSwapChain.Reset();
		m_pDirect2dContext.Reset();
		m_pDirect2dDevice.Reset();
		m_pDirect3dDevice.Reset();
		m_pDirect3dContext.Reset();
	}

	void D2DApp::LoadBitmapFromResource(PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap1 ** ppBitmap)
	{
		ComPtr<IWICBitmapDecoder> pDecoder = nullptr;
		ComPtr<IWICBitmapFrameDecode> pSource = nullptr;
		ComPtr<IWICStream> pStream = nullptr;
		ComPtr<IWICFormatConverter> pConverter = nullptr;
		ComPtr<IWICBitmapScaler> pScaler = nullptr;

		HRSRC imageResHandle = NULL;
		HGLOBAL imageResDataHandle = NULL;
		void *pImageFile = NULL;
		DWORD imageFileSize = 0;

		// 从资源文件定位资源
		imageResHandle = FindResourceW(m_hInstance, resourceName, resourceType);
		ASSERT_OR_THROW(imageResHandle != nullptr);

		// 加载资源
		imageResDataHandle = LoadResource(m_hInstance, imageResHandle);
		ASSERT_OR_THROW(imageResDataHandle != nullptr);

		// 取得资源指针
		pImageFile = LockResource(imageResDataHandle);
		ASSERT_OR_THROW(pImageFile != nullptr);

		// 取得资源大小
		imageFileSize = SizeofResource(m_hInstance, imageResHandle);
		ASSERT_OR_THROW(imageFileSize > 0);

		// 创建流对象，映射至内存
		ThrowIfFailed(m_pWICImagingFactory->CreateStream(&pStream));

		// 分配内存
		ThrowIfFailed(pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize));

		// 创建译码器
		ThrowIfFailed(m_pWICImagingFactory->CreateDecoderFromStream(pStream.Get(), NULL, WICDecodeMetadataCacheOnLoad, &pDecoder));

		// 取得图像帧
		ThrowIfFailed(pDecoder->GetFrame(0, &pSource));

		// 创建格式转换器
		ThrowIfFailed(m_pWICImagingFactory->CreateFormatConverter(&pConverter));

		// 初始化转换器
		ThrowIfFailed(pConverter->Initialize(
			pSource.Get(),
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		));

		// 返回资源中的位图
		ThrowIfFailed(m_pDirect2dContext->CreateBitmapFromWicBitmap(pConverter.Get(), nullptr, ppBitmap));

		// 释放内存
		pDecoder.Reset();
		pSource.Reset();
		pStream.Reset();
		pConverter.Reset();
		pScaler.Reset();
	}

	void D2DApp::PlaySoundFromResource(PCWSTR soundID, PCWSTR soundType)
	{
		HRSRC hGameoverSoundInfo = FindResource(m_hInstance, soundID, soundType);
		ASSERT_OR_THROW(hGameoverSoundInfo != nullptr);
		HGLOBAL hGameoverSound = LoadResource(m_hInstance, hGameoverSoundInfo);
		ASSERT_OR_THROW(hGameoverSound != nullptr);
		LPVOID gameoverSound = LockResource(hGameoverSound);
		ASSERT_OR_THROW(gameoverSound != nullptr);
		sndPlaySound(static_cast<LPCWSTR>(gameoverSound), SND_ASYNC | SND_MEMORY);
	}

	void D2DApp::CalculateFrameStats()
	{
		// 计算一秒钟渲染的帧数（fps）及渲染一帧所需的平均时间（单位：毫秒）
		// 并将这些数值输出到窗口标题栏
		static int frameCnt = 0;
		static float timeElapsed = 0.0f;

		frameCnt++;

		// 每一秒钟计算一次 fps 和 mspf
		if ((m_timer.TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = static_cast<float>(frameCnt); // fps = frameCnt / 1s
			float mspf = 1000.0f / fps;
			
			wstring fpsStr = to_wstring(fps);
			wstring mspfStr = to_wstring(mspf);

			wstring windowText = m_windowCaption +
				L"    fps: " + fpsStr +
				L"   mspf: " + mspfStr;

			SetWindowText(m_hWnd, windowText.c_str());

			// 重置数值，等待下一秒的计算
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}

}