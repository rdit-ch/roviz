
#include "streams/stream_object.h"
#include "streams/stream_object_p.h"

SourceID StreamObject::id() const
{
    return _this_base->id;
}

void StreamObject::initSources(std::initializer_list<SourceID> sources)
{
    if(sources.size() == 0)
    {
        _this_base->id = nullptr;
    }
    else
    {
        _this_base->id = std::make_shared<SrcTreeNode>();
        _this_base->id->sources = std::vector<SourceID>(sources);
    }
}
