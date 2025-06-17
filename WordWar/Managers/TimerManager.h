#pragma once
#include <functional>
#include <atomic>
#include <memory>

struct TimerHandle {
    int intervalMs;
    bool isRepeating;
    std::function<void()> callback;
    std::atomic<bool> isActive = true;

    TimerHandle(int interval, bool repeat, std::function<void()> cb)
        : intervalMs(interval), isRepeating(repeat), callback(cb) {
    }

    void Stop() { isActive = false; }
};

class TimerManager {
public:
    std::shared_ptr<TimerHandle> SetTimer(int intervalMs, std::function<void()> func, bool isRepeating);
};
