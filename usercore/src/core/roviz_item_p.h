#ifndef ROVIZ_ITEM_PRIVATE_H
#define ROVIZ_ITEM_PRIVATE_H

#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>

class RovizItem;

/**
 * @brief Private part of RovizItem
 *
 * \sa RovizItem
 */
class RovizItemPrivate
{
public:
    std::condition_variable cond;
    std::thread *th;
    std::mutex mtx;
    bool is_paused, is_stopped;

    RovizItemPrivate() = default;
    ~RovizItemPrivate() = default;
};

#endif // ROVIZ_ITEM_PRIVATE_H
