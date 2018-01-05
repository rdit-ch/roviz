#ifndef ROVIZ_ITEM_PRIVATE_H
#define ROVIZ_ITEM_PRIVATE_H

#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>

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
    std::list<std::thread*> threads;
    std::mutex mtx;
    bool is_paused, is_stopped, parallelizable;

    RovizItemPrivate() = default;
    ~RovizItemPrivate() = default;
};

#endif // ROVIZ_ITEM_PRIVATE_H
