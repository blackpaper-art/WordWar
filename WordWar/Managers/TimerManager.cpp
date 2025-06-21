#include "TimerManager.h"

#include <chrono>
#include <thread>

// Set a new timer with interval and callback
// 間隔とコールバックを設定して新しいタイマーを作成
std::shared_ptr<TimerHandle> TimerManager::SetTimer(
    int intervalMs, std::function<void()> func, bool isRepeating)
{
    // Create handle
    // ハンドル生成
    auto handle = std::make_shared<TimerHandle>(intervalMs, isRepeating, func);

    // Launch thread for timer loop
    // タイマーループ用のスレッドを起動
    std::thread([handle]() {
        while (handle->isActive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(handle->intervalMs));
            if (!handle->isActive) break;

            try {
                handle->callback(); // Call the function / コールバック実行
            }
            catch (...) {
                // Avoid termination due to unhandled exceptions
                // 例外未処理で終了しないように
            }

            if (!handle->isRepeating) break; // If not repeating, exit / 繰り返しでない場合終了
        }
        }).detach();

    return handle;
}
