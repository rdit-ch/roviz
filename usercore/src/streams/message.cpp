
#include "streams/message.h"
#include "streams/message_p.h"

#include "core/template_decl.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include <QWidget>
#endif

Message::Message(const StreamObject &base)
{
    _this_base = base._this_base;
}

Message::Message(std::string msg_type, std::initializer_list<SourceID> sources)
    : _this(new MessagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);
    _this->type = msg_type;
}

const Message::Entry &Message::entry(const std::string &name) const
{
    for(const auto &entry : _this->entries)
        if(entry.name() == name)
            return entry;

    // Return something invalid if nothing's found
    return _this->default_entry;
}

const Message::Entry &Message::at(int index) const
{
    if(index < this->size() - 1)
        return _this->entries[index];

    // Return something invalid if the index is out of bounds
    return _this->default_entry;
}

const Message::Entry &Message::operator[](int index) const
{
    return _this->entries[index];
}

int Message::size() const
{
    return _this->entries.size();
}

std::string Message::type() const
{
    return _this->type;
}

std::vector<Message::Entry>::const_iterator Message::begin() const
{
    return _this->entries.cbegin();
}

std::vector<Message::Entry>::const_iterator Message::end() const
{
    return _this->entries.cend();
}

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
StreamWidget *Message::initWidget(OutputPrivate *out)
{
    // TODO Implement
    return nullptr;
}
#endif

Message::Entry::Entry(const std::string &name, const std::string &value)
    : name_var(name), value_var(value)
{
}

std::string Message::Entry::name() const
{
    return this->name_var;
}

std::string Message::Entry::value() const
{
    return this->value_var;
}

template<>
int Message::Entry::to<int>() const
{
    return std::stoi(this->value_var);
}

template<>
double Message::Entry::to<double>() const
{
    return std::stod(this->value_var);
}

template<>
std::string Message::Entry::to<std::string>() const
{
    return this->value_var;
}

template<>
bool Message::Entry::to<bool>() const
{
    return this->value_var == "true" ||
           this->value_var == "True" ||
           this->value_var == "TRUE" ||
           this->value_var == "1";
}
