#include "TimerManager.h"

#include <chrono>
#include <thread>

// Set a new timer with interval and callback
// �g���ȥ��`��Хå����O�������¤��������ީ`������
std::shared_ptr<TimerHandle> TimerManager::SetTimer(
    int intervalMs, std::function<void()> func, bool isRepeating)
{
    // Create handle
    // �ϥ�ɥ�����
    auto handle = std::make_shared<TimerHandle>(intervalMs, isRepeating, func);

    // Launch thread for timer loop
    // �����ީ`��`���äΥ���åɤ�����
    std::thread([handle]() {
        while (handle->isActive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(handle->intervalMs));
            if (!handle->isActive) break;

            try {
                handle->callback(); // Call the function / ���`��Хå��g��
            }
            catch (...) {
                // Avoid termination due to unhandled exceptions
                // ����δ�I��ǽK�ˤ��ʤ��褦��
            }

            if (!handle->isRepeating) break; // If not repeating, exit / �R�귵���Ǥʤ����ϽK��
        }
        }).detach();

    return handle;
}
