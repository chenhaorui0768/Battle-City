#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	// 取得性能计数器两刻间时长

	__int64 countsPerSecond;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSecond));	// 取得每秒钟的刻数
	m_secondsPerCount = 1.0 / static_cast<double>(countsPerSecond);					// 取倒数，即为两刻间时长
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
	// 取得当前时刻计数
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

	// 设置开始时间，暂停时间和时钟状态
	m_baseTime = currTime;
	m_prevTime = currTime;
	m_stopTime = 0;
	m_isStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

	// 如果时钟处于暂停状态
	// 计算从调用 Stop 到调用本函数所经历的暂停时间
	if (m_isStopped)
	{
		// 增加暂停时间
		m_pausedTime += (startTime - m_stopTime);

		// 记录开始时间并结束暂停状态
		m_prevTime = startTime;
		m_stopTime = 0;
		m_isStopped = false;
	}
}

void GameTimer::Stop()
{
	// 如果已经暂停，则直接返回
	if (!m_isStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		// 否则，记录当前时间，并标记状态
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

	// 取得这一帧的时刻
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;

	// 计算这一帧的时间和上一帧的时间差
	m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;

	// 为下一帧的计算保存时刻
	m_prevTime = m_currTime;

	// 强制非负
	// 若处理器进入省电模式或程序执行时被切入另一个处理器，那么我们可能得到一个负数时间
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
