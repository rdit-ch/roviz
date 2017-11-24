
#include "backend_cmdline/roviz_item_base_cmdline.h"
#include "backend_cmdline/trim_impl_cmdline.h"
#include "backend_cmdline/config_impl_cmdline.h"

namespace roviz
{

ItemBaseCmdline::ItemBaseCmdline(std::string)
    : _this_base(new ItemBaseCmdlinePrivate())
{
}

bool ItemBaseCmdline::connect(int input_index, ItemBaseCmdline *from_item, int output_index)
{
    // The compiler complains because of signed/unsigned without the typecasts
    if(input_index >= (int)_this_base->inputs.size())
        return false;

    if(output_index >= (int)from_item->_this_base->outputs.size())
        return false;

    _this_base->inputs[input_index]->connect(from_item->_this_base->outputs[output_index]);

    return true;
}

void ItemBaseCmdline::setTrim(std::string name, double value)
{
    std::map<std::string, TrimImplCmdline*>::iterator trim = _this_base->trims.find(name);
    if(trim != _this_base->trims.end())
        trim->second->setValue(value);
}

template<class T>
Input<T> ItemBaseCmdline::addInputBase(std::string , Item *item)
{
    Input<T> input(item);

    _this_base->inputs.push_back(input._this.get());

    return input;
}

template<class T>
Output<T> ItemBaseCmdline::addOutputBase(std::string )
{
    Output<T> output;

    _this_base->outputs.push_back(output._this.get());

    return output;
}

TrimImpl *ItemBaseCmdline::getTrimImpl(std::string name, double, double, double, int, bool, std::function<void (double)>)
{
    TrimImplCmdline *impl = new TrimImplCmdline();

    _this_base->trims[name] = impl;

    return impl;
}

ConfigImpl *ItemBaseCmdline::getConfigImpl(const std::string &name, const ConfigStorageType<int>::type &, int, int, bool)
{
    ConfigImplBaseCmdline *impl = new ConfigImplCmdline<int>();

    _this_base->configs[name] = impl;

    return impl;
}

ConfigImpl *ItemBaseCmdline::getConfigImpl(const std::string &name, const ConfigStorageType<double>::type &, double, double, bool)
{
    ConfigImplBaseCmdline *impl = new ConfigImplCmdline<double>();

    _this_base->configs[name] = impl;

    return impl;
}

ConfigImpl *ItemBaseCmdline::getConfigImpl(const std::string &name, const ConfigStorageType<std::string>::type &, std::function<bool (std::string &)>, bool)
{
    ConfigImplBaseCmdline *impl = new ConfigImplCmdline<std::string>();

    _this_base->configs[name] = impl;

    return impl;
}

ConfigImpl *ItemBaseCmdline::getConfigImpl(const std::string &name, const ConfigStorageType<std::vector<std::string> >::type &, const std::vector<std::string> &, bool )
{
    ConfigImplBaseCmdline *impl = new ConfigImplCmdline<std::vector<std::string> >();

    _this_base->configs[name] = impl;

    return impl;
}

ConfigImpl *ItemBaseCmdline::getConfigImpl(const std::string &name, const ConfigStorageType<bool>::type &, bool )
{
    ConfigImplBaseCmdline *impl = new ConfigImplCmdline<bool>();

    _this_base->configs[name] = impl;

    return impl;
}

ConfigImpl *ItemBaseCmdline::getConfigImpl(const std::string &name, const ConfigStorageType<FilePath>::type &, FilePath::Mode, const std::string &, bool)
{
    ConfigImplBaseCmdline *impl = new ConfigImplCmdline<FilePath>();

    _this_base->configs[name] = impl;

    return impl;
}

void ItemBaseCmdline::start()
{
}

void ItemBaseCmdline::stop()
{
}

#define INSTANTIATE_ROVIZ_ITEM_BASE_CMDLINE(T) \
    template Input<T> RovizItemBaseCmdline::addInputBase<T>(std::string name, RovizItem *item); \
    template Output<T> RovizItemBaseCmdline::addOutputBase<T>(std::string name);

ROVIZ_DO_FOR_ALL_STREAMS(INSTANTIATE_ROVIZ_ITEM_BASE_CMDLINE)

}
