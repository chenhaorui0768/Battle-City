#ifndef GAMETIMER_H
#define GAMETIMER_H

// ��Ϸʱ��
// ʹ�ø߾������ܼ���������ʱ�����
class GameTimer
{
public:
	GameTimer();

	float TotalTime()const;				// ��Ϸʱ��������ʱ��
	float DeltaTime()const;				// ÿ���� Tick ֮���ʱ��

	__int64 CurrentFrame();				// ���ص�ǰ��Ϸ֡��

	void Reset();						// ����ʱ�������
	void Start();						// ��ʱ��ʼ
	void Stop();						// ��ʱ��ͣ
	void Tick();						// ��ÿһ֡���м�ʱ

	void SetFps(UINT Fps);			// ���� FPS
	void BeginCountFps();			// ��ʼ��ʱ
	void WaitForFps();				// �ȴ� FPS

private:
	double	m_secondsPerCount = 0.0;// ���ܼ�����ÿ�̵�ʱ��
	double	m_deltaTime = 0.0;		// ÿ���� Tick ֮���ʱ��

	bool	m_isStopped = false;	// ʱ����ͣ�У�
	__int64 m_baseTime = 0;			// ����ʱ��
	__int64 m_pausedTime = 0;		// ��ͣʱ��
	__int64 m_stopTime = 0;			// ֹͣʱ��
	__int64 m_prevTime = 0;			// ��ʼʱ��
	__int64 m_currTime = 0;			// ��ǰʱ��

	__int64 m_countPerFrame = 0;	// ÿ֡�Ŀ���
	__int64 m_beginCount = 0;		// BeginCountFps ʱ�ļ���
	__int64 m_currentFrame = 0;
};

#endif