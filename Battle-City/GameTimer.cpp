#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	// ȡ�����ܼ��������̼�ʱ��

	__int64 countsPerSecond;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSecond));	// ȡ��ÿ���ӵĿ���
	m_secondsPerCount = 1.0 / static_cast<double>(countsPerSecond);					// ȡ��������Ϊ���̼�ʱ��
}

float GameTimer::TotalTime() const
{
	if (m_isStopped)
	{
		return static_cast<float>(((m_stopTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
	}
	else
	{
		return static_cast<float>(((m_currTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
	}
}

float GameTimer::DeltaTime() const
{
	return static_cast<float>(m_deltaTime);
}

__int64 GameTimer::CurrentFrame()
{
	return m_currentFrame;
}

void GameTimer::Reset()
{
	__int64 currTime;
	// ȡ�õ�ǰʱ�̼���
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

	// ���ÿ�ʼʱ�䣬��ͣʱ���ʱ��״̬
	m_baseTime = currTime;
	m_prevTime = currTime;
	m_stopTime = 0;
	m_isStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

	// ���ʱ�Ӵ�����ͣ״̬
	// ����ӵ��� Stop �����ñ���������������ͣʱ��
	if (m_isStopped)
	{
		// ������ͣʱ��
		m_pausedTime += (startTime - m_stopTime);

		// ��¼��ʼʱ�䲢������ͣ״̬
		m_prevTime = startTime;
		m_stopTime = 0;
		m_isStopped = false;
	}
}

void GameTimer::Stop()
{
	// ����Ѿ���ͣ����ֱ�ӷ���
	if (!m_isStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		// ���򣬼�¼��ǰʱ�䣬�����״̬
		m_stopTime = currTime;
		m_isStopped = true;
	}
}

void GameTimer::Tick()
{
	if (m_isStopped)
	{
		m_deltaTime = 0.0;
		return;
	}

	// ȡ����һ֡��ʱ��
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;

	// ������һ֡��ʱ�����һ֡��ʱ���
	m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;

	// Ϊ��һ֡�ļ��㱣��ʱ��
	m_prevTime = m_currTime;

	// ǿ�ƷǸ�
	// ������������ʡ��ģʽ�����ִ��ʱ��������һ������������ô���ǿ��ܵõ�һ������ʱ��
	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}

	m_currentFrame++;
}

void GameTimer::SetFps(UINT Fps)
{
	double secondPerFrame = 1.0 / static_cast<double>(Fps);
	m_countPerFrame = secondPerFrame / m_secondsPerCount;
}

void GameTimer::BeginCountFps()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_beginCount);
}

void GameTimer::WaitForFps()
{
	__int64 currCount = 0;
	while (true)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currCount);
		if (currCount - m_beginCount >= m_countPerFrame)
			return;
	}
}
