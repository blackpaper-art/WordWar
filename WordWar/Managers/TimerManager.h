#pragma once
#include <functional>
#include <atomic>
#include <memory>

// Timer handle for managing each timer instance
// �����ީ`���󥹥��󥹤������ϥ�ɥ�
struct TimerHandle {
    int intervalMs;                     // Interval in milliseconds / �ߥ���gλ���g��
    bool isRepeating;                   // Whether to repeat / �R�귵���ե饰
    std::function<void()> callback;     // Callback function / ���`��Хå��v��
    std::atomic<bool> isActive = true;  // Active flag / �Є��ե饰

    TimerHandle(int interval, bool repeat, std::function<void()> cb)
        : intervalMs(interval), isRepeating(repeat), callback(cb) {
    }

    void Stop() { isActive = false; } // Stop this timer / �����ީ`��ֹͣ
};

// Manager for setting up timers
// �����ީ`���O������ޥͩ`����`���饹
class TimerManager {
public:
    // Set a new timer
    // �¤��������ީ`���O��
    std::shared_ptr<TimerHandle> SetTimer(int intervalMs, std::function<void()> func, bool isRepeating);
};
