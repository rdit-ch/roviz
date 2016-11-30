#ifndef PORTABLEITEMPRIVATE_H
#define PORTABLEITEMPRIVATE_H

#include "portable/portable_item.h"

class PortableItemPrivate
{
public:
    PortableItem *_this;
    std::map<void*, ImageQueue*> img_in_queue;
    std::condition_variable cond;
    std::thread *th;
    std::mutex mtx;
    bool is_paused, is_stopped;

    PortableItemPrivate(PortableItem *q);
    ~PortableItemPrivate();
};

#endif // PORTABLEITEMPRIVATE_H
