#ifndef D2DEXCEPTION_H
#define D2DEXCEPTION_H

namespace D2DAPP
{
	// D2DApp 异常处理类
	class D2DException
	{
	public:
		D2DException(HRESULT errorCode, int line, wstring functionCall, wstring fileName);

	public:
		// 显示错误信息
		void		ShowError()const;
		// 返回错误信息
		wstring		ToString()const;

	private:
		HRESULT		m_errorCode;
		int			m_line;
		wstring		m_functionCall;
		wstring		m_fileName;
	};

	// 若出现错误则抛出异常
#ifndef ThrowIfFailed
#define ThrowIfFailed(call)									\
{															\
HRESULT hr = call;											\
if(FAILED(hr))												\
{															\
throw D2DAPP::D2DException(hr,__LINE__,L#call,__FILEW__);	\
}															\
}

#endif // !ThrowIfFailed

}

#endif
