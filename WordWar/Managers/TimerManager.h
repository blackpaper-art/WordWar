#pragma once
#include <functional>
#include <atomic>
#include <memory>

// Timer handle for managing each timer instance
// タイマーインスタンスを管理するハンドル
struct TimerHandle {
    int intervalMs;                     // Interval in milliseconds / ミリ秒単位の間隔
    bool isRepeating;                   // Whether to repeat / 繰り返しフラグ
    std::function<void()> callback;     // Callback function / コールバック関数
    std::atomic<bool> isActive = true;  // Active flag / 有効フラグ

    TimerHandle(int interval, bool repeat, std::function<void()> cb)
        : intervalMs(interval), isRepeating(repeat), callback(cb) {
    }

    void Stop() { isActive = false; } // Stop this timer / タイマーを停止
};

// Manager for setting up timers
// タイマーを設定するマネージャークラス
class TimerManager {
public:
    // Set a new timer
    // 新しいタイマーを設定
    std::shared_ptr<TimerHandle> SetTimer(int intervalMs, std::function<void()> func, bool isRepeating);
};
