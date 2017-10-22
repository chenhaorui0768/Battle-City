#ifndef GAMETIMER_H
#define GAMETIMER_H

// 游戏时钟
// 使用高精度性能计数器进行时间计算
class GameTimer
{
public:
	GameTimer();

	float TotalTime()const;				// 游戏时钟运行总时间
	float DeltaTime()const;				// 每两次 Tick 之间的时间

	__int64 CurrentFrame();				// 返回当前游戏帧数

	void Reset();						// 重置时间计数器
	void Start();						// 计时开始
	void Stop();						// 计时暂停
	void Tick();						// 在每一帧进行计时

	void SetFps(UINT Fps);			// 设置 FPS
	void BeginCountFps();			// 开始计时
	void WaitForFps();				// 等待 FPS

private:
	double	m_secondsPerCount = 0.0;// 性能计数器每刻的时长
	double	m_deltaTime = 0.0;		// 每两次 Tick 之间的时间

	bool	m_isStopped = false;	// 时钟暂停中？
	__int64 m_baseTime = 0;			// 重置时刻
	__int64 m_pausedTime = 0;		// 暂停时间
	__int64 m_stopTime = 0;			// 停止时刻
	__int64 m_prevTime = 0;			// 开始时刻
	__int64 m_currTime = 0;			// 当前时刻

	__int64 m_countPerFrame = 0;	// 每帧的刻数
	__int64 m_beginCount = 0;		// BeginCountFps 时的计数
	__int64 m_currentFrame = 0;
};

#endif