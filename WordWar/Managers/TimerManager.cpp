#include "TimerManager.h"

#include <chrono>

std::shared_ptr<TimerHandle> TimerManager::SetTimer(int intervalMs, std::function<void()> func, bool isRepeating) {
    auto handle = std::make_shared<TimerHandle>(intervalMs, isRepeating, func);

    std::thread([handle]() {
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(handle->intervalMs));
            if (!handle->isActive) break;
            handle->callback();
        } while (handle->isRepeating && handle->isActive);
        }).detach();

    return handle;
}
