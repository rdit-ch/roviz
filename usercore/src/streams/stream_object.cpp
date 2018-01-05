
#include "streams/stream_object.h"
#include "streams/stream_object_p.h"

#include "core/output_p.h"

SourceID StreamObject::id() const
{
    return _this_base->id;
}

void StreamObject::setSequenceNumber(unsigned int seq_nr)
{
    _this_base->id->seq_nr = seq_nr;
}

void StreamObject::initRelations(RovizItem *item, unsigned int seq_nr)
{
    _this_base->id->item = item;

    if(_this_base->id->seq_nr == 0)
        _this_base->id->seq_nr = seq_nr;
}

void StreamObject::initSources(std::initializer_list<SourceID> sources)
{
    _this_base->id = std::make_shared<SrcTreeNode>();
    _this_base->id->sources = std::vector<SourceID>(sources);

    if(sources.size() == 0)
        _this_base->id->seq_nr = 0;
    else
        _this_base->id->seq_nr = sources.begin()->get()->seq_nr;
}
