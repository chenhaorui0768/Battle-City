#ifndef D2DAPP_H
#define D2DAPP_H

namespace D2DAPP
{
	class D2DApp
	{
	public:
		D2DApp();

		virtual bool	Init(HINSTANCE hInstance);				// 总初始化
		virtual bool	InitMainWindow();						// 初始化窗口
		virtual bool	InitDirect2D();							// 初始化 Direct2D
		virtual bool	Release();								// 释放 Direct2D 对象
		virtual int		Run();									// 进入消息循环

		friend	LRESULT	CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// 返回当前实例
		static D2DApp*	GetApp();

		// 返回游戏fps
		int				GetFps();
	protected:
		// 窗口过程函数
		virtual LRESULT	MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual void	CreateDeviceIndependentResources();		// 创建设备无关资源
		virtual void	CreateDeviceResources();				// 创建设备相关资源
		virtual void	CreateWindowSizeResources();			// 创建窗口大小相关资源
		virtual void	DiscardDeviceResources();				// 释放设备相关资源

		// 从资源文件中加载位图资源
		void			LoadBitmapFromResource(	PCWSTR resourceName,
												PCWSTR resourceType,
												UINT destinationWidth,
												UINT destinationHeight,
												ID2D1Bitmap1 **ppBitmap);

		// 从资源文件中播放音频
		void			PlaySoundFromResource(	PCWSTR soundID,
												PCWSTR soundType);

		// 计算fps
		void			CalculateFrameStats();

		// 图像绘制
		virtual void	DrawScene() = 0;
		virtual void	UpdateScene() = 0;
		

	// 消息处理函数
	protected:
		virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);											// WM_CREATE
		virtual LRESULT OnPaint();																			// WM_PAINT
		virtual LRESULT OnSize(UINT nType, int windowWidth, int windowHeight);								// WM_SIZE
		virtual LRESULT OnMoving(RECT *rect);																// WM_MOVING
		virtual LRESULT OnMove(int x, int y);																// WM_MOVE
		virtual LRESULT OnDestroy();																		// WM_DESTROY

		virtual LRESULT OnMouseDown(UINT btnState, int x, int y);											// 按下鼠标按钮
		virtual LRESULT OnMouseUp(UINT btnState, int x, int y);												// 放开鼠标按钮
		virtual LRESULT OnMouseMove(UINT btnState, int x, int y);											// 移动鼠标

		virtual LRESULT OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags);									// WM_KEYDOWN
		virtual LRESULT OnKeyup(UINT nChar, UINT nRepCnt, UINT nFlags);										// WM_KEYUP

	protected:
		// Direct2D 及其相关核心接口
		ComPtr<IDXGISwapChain4>			m_pdxgiSwapChain = nullptr;		// DXGI 交换链
		ComPtr<ID3D11Device5>			m_pDirect3dDevice = nullptr;	// Direct3D 设备
		ComPtr<ID3D11DeviceContext4>	m_pDirect3dContext = nullptr;	// Direct3D 设备上下文
		ComPtr<IWICImagingFactory2>		m_pWICImagingFactory = nullptr;	// WIC 工厂
		ComPtr<IDWriteFactory5>			m_pDWriteFactory = nullptr;		// DirectWrite 工厂
		ComPtr<ID2D1Device5>			m_pDirect2dDevice = nullptr;	// Direct2D 设备
		ComPtr<ID2D1Factory5>			m_pDirect2dFactory = nullptr;	// Direct2D 工厂
		ComPtr<ID2D1DeviceContext5>		m_pDirect2dContext = nullptr;	// Direct2D 设备上下文
		ComPtr<ID2D1Bitmap1>			m_pDirect2dBitmap = nullptr;	// Direct2D 位图

		HINSTANCE						m_hInstance = nullptr;			// 实例句柄
		HWND							m_hWnd = nullptr;				// 窗口句柄
		int								m_clientWidth = 800;			// 窗口宽度
		int								m_clientHeight = 600;			// 窗口高度
		int								m_fps = 60;						// 帧每秒
		wstring							m_windowCaption = L"D2DApp";	// 窗口标题
		WNDCLASSEX						m_wndClass = {};				// 窗口类
		CREATESTRUCT					m_createStruct = {};			// 窗口结构
		GameTimer						m_timer;						// 时钟
		bool							m_bPaused = false;				// 应用暂停
		bool							m_bHandled = false;				// 消息是否已经处理

		thread							m_renderThread;					// 窗口渲染线程
		static D2DApp*					m_spApp;						// 运行中的程序实例
	};
}

inline void DrawBitmap(ID2D1DeviceContext* context, ID2D1Bitmap1 *bitmap, float left, float top)
{
	context->DrawBitmap(bitmap,
		D2D1::RectF(left, top, left + bitmap->GetSize().width, top + bitmap->GetSize().height));
}

inline void DrawText(ID2D1DeviceContext* context,
	IDWriteTextFormat* format, ID2D1Brush *brush,
	const wstring &text, float left, float top, float clientWidth, float clientHeight)
{
	context->DrawTextW(text.c_str(), text.length(), format,
		D2D1::RectF(left, top, clientWidth, clientWidth), brush);
}

#endif