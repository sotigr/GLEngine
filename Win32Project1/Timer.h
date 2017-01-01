#pragma once
#include <ctime>
class Timer
{
	clock_t startedAt;
	clock_t pausedAt;
	bool started;
	bool paused;
public:
	Timer();
	bool IsStarted();
	bool IsStopped();
	bool IsPaused();
	bool IsActive();
	void Pause();
	void Resume();
	void Stop();
	void Start();
	void Reset();
	clock_t GetTicks();
};
 