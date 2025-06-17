#include "TimerManager.h"

#include <chrono>
#include <thread>

std::shared_ptr<TimerHandle> TimerManager::SetTimer(
    int intervalMs, std::function<void()> func, bool isRepeating)
{
    auto handle = std::make_shared<TimerHandle>(intervalMs, isRepeating, func);

    std::thread([handle]() {
        while (handle->isActive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(handle->intervalMs));
            if (!handle->isActive) break;

            try {
                handle->callback();
            }
            catch (...) {
                // ±ÜÃâÎ´²¶»ñÒì³£µ¼ÖÂ terminate
            }

            if (!handle->isRepeating) break;
        }
        }).detach();

    return handle;
}