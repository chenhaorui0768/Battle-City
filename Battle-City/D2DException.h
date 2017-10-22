#ifndef D2DEXCEPTION_H
#define D2DEXCEPTION_H

namespace D2DAPP
{
	// D2DApp �쳣������
	class D2DException
	{
	public:
		D2DException(HRESULT errorCode, int line, wstring functionCall, wstring fileName);

	public:
		// ��ʾ������Ϣ
		void		ShowError()const;
		// ���ش�����Ϣ
		wstring		ToString()const;

	private:
		HRESULT		m_errorCode;
		int			m_line;
		wstring		m_functionCall;
		wstring		m_fileName;
	};

	// �����ִ������׳��쳣
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
