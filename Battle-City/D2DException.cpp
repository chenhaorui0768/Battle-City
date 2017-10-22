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
		MessageBoxW(nullptr, ToString().c_str(), L"D2D 错误", MB_OK);
	}

	wstring D2DException::ToString() const
	{
		// 取得错误信息
		_com_error error(m_errorCode);
		wstring errorMsg = error.ErrorMessage();
		// 返回错误信息
		return m_fileName + L"中函数" + m_functionCall + L"调用失败，该调用位于第 " + std::to_wstring(m_line) + L" 行，错误信息为：" + errorMsg;
	}
}
