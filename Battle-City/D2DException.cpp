#include "stdafx.h"
#include "D2DException.h"

namespace D2DAPP
{
	D2DException::D2DException(HRESULT errorCode, int line, wstring functionCall, wstring fileName)
	{
		m_errorCode = errorCode;
		m_line = line;
		m_functionCall = functionCall;
		m_fileName = fileName;
	}

	void D2DException::ShowError() const
	{
		MessageBoxW(nullptr, ToString().c_str(), L"D2D ����", MB_OK);
	}

	wstring D2DException::ToString() const
	{
		// ȡ�ô�����Ϣ
		_com_error error(m_errorCode);
		wstring errorMsg = error.ErrorMessage();
		// ���ش�����Ϣ
		return m_fileName + L"�к���" + m_functionCall + L"����ʧ�ܣ��õ���λ�ڵ� " + std::to_wstring(m_line) + L" �У�������ϢΪ��" + errorMsg;
	}
}
