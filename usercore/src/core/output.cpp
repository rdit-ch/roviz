
#include "core/output.h"

#include "core/template_decl.h"
#include "core/logger.h"
#include "streams/all_streams.h"

namespace roviz
{

template<class T>
Output<T>::Output()
    : _this(new OutputPrivate())
{
}

template<class T>
void Output<T>::pushOut(T obj)
{
    for(const auto &pushIn : _this->pushInFuncs)
        pushIn(obj);
}

#define INSTANTIATE_OUTPUT(T) template class Output<T >;

ROVIZ_DO_FOR_ALL_STREAMS(INSTANTIATE_OUTPUT)

}
