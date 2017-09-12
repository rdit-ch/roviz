#ifndef PORTABLEITEMPRIVATE_H
#define PORTABLEITEMPRIVATE_H

#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "core/typedecl.h"
#include "core/input_queue.h"
#include "config/config_base.h"

/**
 * @brief Private part of RovizItem
 *
 * \sa RovizItem
 */
class RovizItemPrivate
{
public:
    RovizItem *_this;
    std::map<Input, InputQueue*> in_queue;
    std::condition_variable cond;
    std::thread *th;
    std::mutex mtx;
    bool is_paused, is_stopped;

    RovizItemPrivate() = default;
    ~RovizItemPrivate() = default;
};

#endif // PORTABLEITEMPRIVATE_H
