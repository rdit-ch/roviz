
#include "core/output.h"

#include "core/template_decl.h"
#include "streams/all_streams.h"

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

// Yes, that needs to be here. If you change anything (including the order),
// bugs from hell will be summoned.
INSTANTIATE_SPARSE

INSTANTIATE_OUTPUT
