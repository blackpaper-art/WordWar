#pragma once
#include <functional>

class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	void SetTimer(int intervalMs, std::function<void()> func, bool isRepeating);
private:

};
