
#include "core/output_p.h"
#include "core/input_p.h"

namespace roviz
{

OutputPrivate::~OutputPrivate()
{
    for(auto input : this->connected_inputs)
        input->disconnect();
}

OutputPrivate::Connection OutputPrivate::connect(InputPrivate *in, std::function<void (StreamObject)> fn)
{
    std::lock_guard<std::mutex> g(this->mtx);

    this->pushInFuncs.push_front(fn);

    // We can also connect thing other than an input, e.g. a widget (which doesn't have to be disconnected)
    if(in != nullptr)
        this->connected_inputs.push_back(in);

    return this->pushInFuncs.cbegin();
}

void OutputPrivate::disconnect(InputPrivate *in, OutputPrivate::Connection conn)
{
    this->connected_inputs.remove(in);
    this->pushInFuncs.erase(conn);
}

}
