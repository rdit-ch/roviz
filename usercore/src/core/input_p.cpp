
#include "core/input_p.h"
#include "core/roviz_item.h"

namespace roviz
{

InputPrivate::InputPrivate()
{
    this->last_output = nullptr;
}

InputPrivate::~InputPrivate()
{
    if(this->last_output != nullptr)
        this->last_output->disconnect(this, this->connection);
}

void InputPrivate::pushIn(StreamObject obj)
{
    std::lock_guard<std::mutex> g(this->item->mutex());

    this->objects.push_back(obj);
    this->item->wake();
}

void InputPrivate::connect(OutputPrivate *output)
{
    if(this->last_output != nullptr)
        this->last_output->disconnect(this, this->connection);

    if(output != nullptr)
        this->connection = output->connect(this, [this](StreamObject obj){this->pushIn(obj);});

    this->last_output = output;
}

// We need this in case the output gets destructed first, so that we don't access a dangling
// pointer when trying to disconnect the previous output at a reconnect.
void InputPrivate::disconnect()
{
    this->last_output = nullptr;
}

}
