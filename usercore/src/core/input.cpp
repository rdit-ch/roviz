
#include "core/input.h"

#include <mutex>
#include "core/roviz_item.h"
#include "core/template_decl.h"
#include "streams/all_streams.h"

template<class T>
Input<T>::Input(RovizItem *item)
    : _this(new InputPrivate())
{
    _this->item = item;
}

template<class T>
T Input<T>::next()
{
    std::lock_guard<std::mutex> g(_this->item->mutex());

    StreamObject obj = _this->objects.front();
    _this->objects.pop_front();

    return T(obj);
}

template<class T>
T Input<T>::newest()
{
    std::lock_guard<std::mutex> g(_this->item->mutex());

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

DO_FOR_ALL_STREAMS(INSTANTIATE_INPUT)
