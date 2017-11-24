#ifndef ROVIZ_ITEM_PRIVATE_H
#define ROVIZ_ITEM_PRIVATE_H

#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace roviz
{

class Item;

/**
 * @brief Private part of RovizItem
 *
 * \sa RovizItem
 */
class ItemPrivate
{
public:
    std::condition_variable cond;
    std::thread *th;
    std::mutex mtx;
    bool is_paused, is_stopped;

    ItemPrivate() = default;
    ~ItemPrivate() = default;
};

}

#endif // ROVIZ_ITEM_PRIVATE_H
