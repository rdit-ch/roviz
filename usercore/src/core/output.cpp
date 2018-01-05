
#include "core/output.h"

#include "core/template_decl.h"
#include "streams/all_streams.h"

template<class T>
Output<T>::Output(RovizItem *item)
    : _this(new OutputPrivate())
{
    _this->parent_item = item;
}

template<class T>
void Output<T>::pushOut(T obj)
{
    obj.initRelations(_this->parent_item, _this->next_new_seq_nr++);
    for(const auto &pushIn : _this->pushInFuncs)
        pushIn(obj);
}

#define INSTANTIATE_OUTPUT(T) template class Output<T >;

DO_FOR_ALL_STREAMS(INSTANTIATE_OUTPUT)
