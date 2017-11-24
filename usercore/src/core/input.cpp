
#include "core/input.h"

#include <mutex>
#include "core/roviz_item.h"
#include "core/template_decl.h"
#include "core/logger.h"
#include "streams/all_streams.h"

namespace roviz
{

template<class T>
Input<T>::Input(Item *item)
    : _this(new InputPrivate())
{
    logger->error_if(item == nullptr, "Trying to construct an input with a null-item");

    _this->item = item;
}

template<class T>
T Input<T>::next()
{
    std::lock_guard<std::mutex> g(_this->item->mutex());

    if(_this->objects.empty())
    {
        logger->warn("Trying to access empty input queue");
        return T();
    }

    StreamObject obj = _this->objects.front();
    _this->objects.pop_front();

    return T(obj);
}

template<class T>
T Input<T>::newest()
{
    std::lock_guard<std::mutex> g(_this->item->mutex());

    if(_this->objects.empty())
    {
        logger->warn("Trying to access empty input queue");
        return T();
    }

    StreamObject obj = _this->objects.back();
    _this->objects.clear();

    return T(obj);
}

template<class T>
bool Input<T>::waitForInput()
{
    return _this->item->waitForCond([this]{return !this->_this->objects.empty();});
}

#define INSTANTIATE_INPUT(T) template class Input<T >;

ROVIZ_DO_FOR_ALL_STREAMS(INSTANTIATE_INPUT)

}
