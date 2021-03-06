
#include "backend_cmdline/config_impl_cmdline.h"
#include "core/template_decl.h"

template<class T>
void *ConfigImplCmdline<T>::value()
{
    return &this->val;
}

template<>
void ConfigImplCmdline<int>::load(std::string value)
{
    this->val = std::stoi(value);
}

template<>
void ConfigImplCmdline<double>::load(std::string value)
{
    this->val = std::stod(value);
}

template<>
void ConfigImplCmdline<std::string>::load(std::string value)
{
    this->val = value;
}

template<>
void ConfigImplCmdline<std::list<std::string> >::load(std::string value)
{
    // TODO Implement
}

template<>
void ConfigImplCmdline<bool>::load(std::string value)
{
    this->val = (value == "true"); // TODO Yet to be tested
}

template<>
void ConfigImplCmdline<FilePath>::load(std::string value)
{
    std::string::size_type delim;
    std::list<std::string> list;

    while((delim = value.find(';')) != value.npos)
    {
        list.push_back(value.substr(0, delim));
        value.erase(0, delim + 1);
    }
    list.push_back(value);

    this->val = list;
}

template<class T>
void ConfigImplCmdline<T>::lock()
{
}

template<class T>
void ConfigImplCmdline<T>::unlock()
{
}

template<class T>
bool ConfigImplCmdline<T>::changed()
{
    return false;
}

INSTANTIATE_CONFIG_IMPL
