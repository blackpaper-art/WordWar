#pragma once
#include <functional>
#include <mutex>
#include <unordered_map>
#include <atomic>

class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	void SetTimer(int intervalMs, std::function<void()> func, bool isRepeating);
private:
};
