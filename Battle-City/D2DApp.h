#ifndef D2DAPP_H
#define D2DAPP_H

namespace D2DAPP
{
	class D2DApp
	{
	public:
		D2DApp();

		virtual bool	Init(HINSTANCE hInstance);				// �ܳ�ʼ��
		virtual bool	InitMainWindow();						// ��ʼ������
		virtual bool	InitDirect2D();							// ��ʼ�� Direct2D
		virtual bool	Release();								// �ͷ� Direct2D ����
		virtual int		Run();									// ������Ϣѭ��

		friend	LRESULT	CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// ���ص�ǰʵ��
		static D2DApp*	GetApp();

		// ������Ϸfps
		int				GetFps();
	protected:
		// ���ڹ��̺���
		virtual LRESULT	MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual void	CreateDeviceIndependentResources();		// �����豸�޹���Դ
		virtual void	CreateDeviceResources();				// �����豸�����Դ
		virtual void	CreateWindowSizeResources();			// �������ڴ�С�����Դ
		virtual void	DiscardDeviceResources();				// �ͷ��豸�����Դ

		// ����Դ�ļ��м���λͼ��Դ
		void			LoadBitmapFromResource(	PCWSTR resourceName,
												PCWSTR resourceType,
												UINT destinationWidth,
												UINT destinationHeight,
												ID2D1Bitmap1 **ppBitmap);

		// ����Դ�ļ��в�����Ƶ
		void			PlaySoundFromResource(	PCWSTR soundID,
												PCWSTR soundType);

		// ����fps
		void			CalculateFrameStats();

		// ͼ�����
		virtual void	DrawScene() = 0;
		virtual void	UpdateScene() = 0;
		

	// ��Ϣ������
	protected:
		virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);											// WM_CREATE
		virtual LRESULT OnPaint();																			// WM_PAINT
		virtual LRESULT OnSize(UINT nType, int windowWidth, int windowHeight);								// WM_SIZE
		virtual LRESULT OnMoving(RECT *rect);																// WM_MOVING
		virtual LRESULT OnMove(int x, int y);																// WM_MOVE
		virtual LRESULT OnDestroy();																		// WM_DESTROY

		virtual LRESULT OnMouseDown(UINT btnState, int x, int y);											// ������갴ť
		virtual LRESULT OnMouseUp(UINT btnState, int x, int y);												// �ſ���갴ť
		virtual LRESULT OnMouseMove(UINT btnState, int x, int y);											// �ƶ����

		virtual LRESULT OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags);									// WM_KEYDOWN
		virtual LRESULT OnKeyup(UINT nChar, UINT nRepCnt, UINT nFlags);										// WM_KEYUP

	protected:
		// Direct2D ������غ��Ľӿ�
		ComPtr<IDXGISwapChain4>			m_pdxgiSwapChain = nullptr;		// DXGI ������
		ComPtr<ID3D11Device5>			m_pDirect3dDevice = nullptr;	// Direct3D �豸
		ComPtr<ID3D11DeviceContext4>	m_pDirect3dContext = nullptr;	// Direct3D �豸������
		ComPtr<IWICImagingFactory2>		m_pWICImagingFactory = nullptr;	// WIC ����
		ComPtr<IDWriteFactory5>			m_pDWriteFactory = nullptr;		// DirectWrite ����
		ComPtr<ID2D1Device5>			m_pDirect2dDevice = nullptr;	// Direct2D �豸
		ComPtr<ID2D1Factory5>			m_pDirect2dFactory = nullptr;	// Direct2D ����
		ComPtr<ID2D1DeviceContext5>		m_pDirect2dContext = nullptr;	// Direct2D �豸������
		ComPtr<ID2D1Bitmap1>			m_pDirect2dBitmap = nullptr;	// Direct2D λͼ

		HINSTANCE						m_hInstance = nullptr;			// ʵ�����
		HWND							m_hWnd = nullptr;				// ���ھ��
		int								m_clientWidth = 800;			// ���ڿ��
		int								m_clientHeight = 600;			// ���ڸ߶�
		int								m_fps = 60;						// ֡ÿ��
		wstring							m_windowCaption = L"D2DApp";	// ���ڱ���
		WNDCLASSEX						m_wndClass = {};				// ������
		CREATESTRUCT					m_createStruct = {};			// ���ڽṹ
		GameTimer						m_timer;						// ʱ��
		bool							m_bPaused = false;				// Ӧ����ͣ
		bool							m_bHandled = false;				// ��Ϣ�Ƿ��Ѿ�����

		thread							m_renderThread;					// ������Ⱦ�߳�
		static D2DApp*					m_spApp;						// �����еĳ���ʵ��
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