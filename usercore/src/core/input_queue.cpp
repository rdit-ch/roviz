
#include "core/input_queue.h"

InputQueue::InputQueue()
{
}

void InputQueue::push(StreamObject obj)
{
    std::lock_guard<std::mutex> g(this->mtx);
    this->objects.push_back(obj);
}

StreamObject InputQueue::next()
{
    std::lock_guard<std::mutex> g(this->mtx);
    StreamObject obj = this->objects.front();
    this->objects.pop_front();
    return obj;
}

StreamObject InputQueue::newest()
{
    std::lock_guard<std::mutex> g(this->mtx);
    StreamObject obj = this->objects.back();
    this->objects.clear();
    return obj;
}

bool InputQueue::available()
{
    std::lock_guard<std::mutex> g(this->mtx);
    return !this->objects.empty();
}
