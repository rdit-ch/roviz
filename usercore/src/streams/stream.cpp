
#include "core/template_decl.h"
#include "streams/stream.h"
#include "streams/all_streams.h"

INSTANTIATE_STREAM

template<class T>
Stream<T>::Stream()
{
#ifndef ROVIZ_EXPORT
    // I haven't found an elegant way to enforce T to have
    // T::initWidget() without a lot of base ambiguity trouble.
    // Just make sure the stream objects have this method.
    this->widget_ptr = T::initWidget(this);
#endif
}
