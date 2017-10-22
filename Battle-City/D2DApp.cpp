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
		// ���ô�����
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

		// ���� CreateStruct
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
			// ��ʾ��ˢ�´��ڣ����� WM_PAINT��
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
		// ע�ᴰ����
		if (!RegisterClassEx(&m_wndClass))
		{
			MessageBox(0, L"RegisterClass Failed.", 0, 0);
			return false;
		}

		// ���ô��ڴ�С
		RECT R = { 0, 0, m_clientWidth, m_clientHeight };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);

		// ��������
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
		// ���� Direct2D ����
		ThrowIfFailed(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&m_pDirect2dFactory)));
		// ���� WIC ����
		ThrowIfFailed(CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICImagingFactory)));
		// ���� DirectWrite ����
		ThrowIfFailed(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown**>(m_pDWriteFactory.GetAddressOf())));
	}

	void D2DApp::CreateDeviceResources()
	{
		// ���ô��� D3D �豸ʱ�� flag��BGRA ֧�ֺ͵��Բ㣩
		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// ���� Direct3D �豸����������
		ComPtr<ID3D11Device> pDirect3dDevice = nullptr;
		ComPtr<ID3D11DeviceContext> pDirect3dContext = nullptr;
		{
			// ���� Direct3D 11 �豸������Ӳ����
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

			// ������ʧ�ܣ������ WARP �����豸
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

			// ȡ�ýӿ�Ϊ 11.5 �汾���豸��������
			ThrowIfFailed(pDirect3dDevice.As(&m_pDirect3dDevice));
			ThrowIfFailed(pDirect3dContext.As(&m_pDirect3dContext));
		}
		
		// ���� DXGI �豸
		ComPtr<IDXGIDevice4> pdxgiDevice = nullptr;
		ThrowIfFailed(m_pDirect3dDevice.As(&pdxgiDevice));

		// ���� Direct2D �豸
		ComPtr<ID2D1Device> pDirect2dDevice = nullptr;
		ThrowIfFailed(m_pDirect2dFactory->CreateDevice(pdxgiDevice.Get(), &pDirect2dDevice));
		ThrowIfFailed(pDirect2dDevice.As(&m_pDirect2dDevice));

		// ���� Direct2D �豸������
		ThrowIfFailed(m_pDirect2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_pDirect2dContext));

		// �������ڴ�С�����Դ
		CreateWindowSizeResources();
	}

	void D2DApp::CreateWindowSizeResources()
	{
		ComPtr<IDXGIDevice4> pdxgiDevice = nullptr;
		ComPtr<IDXGIAdapter> pdxgiAdapter = nullptr;
		ComPtr<IDXGIFactory5> pdxgiFactory = nullptr;
		ComPtr<IDXGISwapChain1> pdxgiSwapChain = nullptr;
		ComPtr<IDXGISurface2> pdxgiSurface = nullptr;

		// ������ǰ�ĳ�������Դ
		m_pDirect2dContext->SetTarget(nullptr);
		m_pDirect2dBitmap.Reset();
		m_pDirect3dContext->Flush();

		// ���������Ѵ��ڣ���ˢ�½�����������
		if (m_pdxgiSwapChain != nullptr)
		{
			ThrowIfFailed(m_pdxgiSwapChain->ResizeBuffers(2,	// �������еĻ�����
				m_clientWidth,									// ���
				m_clientHeight,									// �߶�
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0));
		}
		// �����ڣ�����������
		else
		{
			// ������������
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
			swapChainDesc.Width = m_clientWidth;							// ���
			swapChainDesc.Height = m_clientHeight;							// �߶�
			swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// ���ظ�ʽ
			swapChainDesc.Stereo = false;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 2;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			swapChainDesc.Flags = 0;
			swapChainDesc.Scaling = DXGI_SCALING_NONE;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

			// ��ȡ DXGI �豸
			ThrowIfFailed(m_pDirect3dDevice.As(&pdxgiDevice));

			// ��ȡ DXGI ������
			ThrowIfFailed(pdxgiDevice->GetAdapter(&pdxgiAdapter));

			// ��ȡ DXGI ����
			ThrowIfFailed(pdxgiAdapter->GetParent(IID_PPV_ARGS(&pdxgiFactory)));

			// ����������
			ThrowIfFailed(pdxgiFactory->CreateSwapChainForHwnd(
				m_pDirect3dDevice.Get(),
				m_hWnd,
				&swapChainDesc,
				nullptr,
				nullptr,
				&pdxgiSwapChain));
			pdxgiSwapChain.As(&m_pdxgiSwapChain);

			// ���� DXGI ���������һ֡
			ThrowIfFailed(pdxgiDevice->SetMaximumFrameLatency(1));
		}

		// ������Ļ����
		ThrowIfFailed(m_pdxgiSwapChain->SetRotation(DXGI_MODE_ROTATION_IDENTITY));

		// ��ȡ DXGI ����
		ThrowIfFailed(m_pdxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&pdxgiSurface)));

		// ����λͼ
		D2D1_BITMAP_PROPERTIES1 bitmapProperties = BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96.0f,
			96.0f);

		ThrowIfFailed(m_pDirect2dContext->CreateBitmapFromDxgiSurface(
			pdxgiSurface.Get(),
			bitmapProperties,
			&m_pDirect2dBitmap));

		// ������ȾĿ��
		m_pDirect2dContext->SetTarget(m_pDirect2dBitmap.Get());
	}

	void D2DApp::DiscardDeviceResources()
	{
		// ���������෴˳���ͷ�
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

		// ����Դ�ļ���λ��Դ
		imageResHandle = FindResourceW(m_hInstance, resourceName, resourceType);
		ASSERT_OR_THROW(imageResHandle != nullptr);

		// ������Դ
		imageResDataHandle = LoadResource(m_hInstance, imageResHandle);
		ASSERT_OR_THROW(imageResDataHandle != nullptr);

		// ȡ����Դָ��
		pImageFile = LockResource(imageResDataHandle);
		ASSERT_OR_THROW(pImageFile != nullptr);

		// ȡ����Դ��С
		imageFileSize = SizeofResource(m_hInstance, imageResHandle);
		ASSERT_OR_THROW(imageFileSize > 0);

		// ����������ӳ�����ڴ�
		ThrowIfFailed(m_pWICImagingFactory->CreateStream(&pStream));

		// �����ڴ�
		ThrowIfFailed(pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize));

		// ����������
		ThrowIfFailed(m_pWICImagingFactory->CreateDecoderFromStream(pStream.Get(), NULL, WICDecodeMetadataCacheOnLoad, &pDecoder));

		// ȡ��ͼ��֡
		ThrowIfFailed(pDecoder->GetFrame(0, &pSource));

		// ������ʽת����
		ThrowIfFailed(m_pWICImagingFactory->CreateFormatConverter(&pConverter));

		// ��ʼ��ת����
		ThrowIfFailed(pConverter->Initialize(
			pSource.Get(),
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		));

		// ������Դ�е�λͼ
		ThrowIfFailed(m_pDirect2dContext->CreateBitmapFromWicBitmap(pConverter.Get(), nullptr, ppBitmap));

		// �ͷ��ڴ�
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
		// ����һ������Ⱦ��֡����fps������Ⱦһ֡�����ƽ��ʱ�䣨��λ�����룩
		// ������Щ��ֵ��������ڱ�����
		static int frameCnt = 0;
		static float timeElapsed = 0.0f;

		frameCnt++;

		// ÿһ���Ӽ���һ�� fps �� mspf
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

			// ������ֵ���ȴ���һ��ļ���
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}

}