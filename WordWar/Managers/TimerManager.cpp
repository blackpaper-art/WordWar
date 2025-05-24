#include "TimerManager.h"

#include <thread>

TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
}

void TimerManager::SetTimer(int intervalMs, std::function<void()> func, bool isRepeating)
{
    std::thread([=]()
        {
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
                func();
            } while (isRepeating);
        }).detach();
}
