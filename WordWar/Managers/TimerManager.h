#pragma once
#include <functional>
#include <mutex>
#include <atomic>
#include <map>
#include <thread>

struct TimerHandle
{
	std::atomic<bool> isActive{ true };
	int intervalMs;
	bool isRepeating;
	std::function<void()> callback;

	TimerHandle(int interval, bool repeat, std::function<void()> cb)
		: intervalMs(interval), isRepeating(repeat), callback(std::move(cb)) {
	}
};

class TimerManager
{
public:
	std::shared_ptr<TimerHandle> SetTimer(int intervalMs, std::function<void()> func, bool isRepeating);
};
