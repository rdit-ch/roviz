
#include "config/config.h"

#include "core/template_decl.h"
#include "config/file_path.h"

template<typename T>
Config<T>::Config()
{
    _this = nullptr;
}

template<>
Config<int>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed)
    : _this(new ConfigPrivate<int>())
{
    _this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(min, max);
}

template<>
Config<double>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed)
    : _this(new ConfigPrivate<double>())
{
    _this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(min, max);
}

template<>
Config<std::string>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed)
    : _this(new ConfigPrivate<std::string>())
{
    _this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(checker);
}

template<>
Config<std::list<std::string> >::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<std::list<std::string> >::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed)
    : _this(new ConfigPrivate<std::list<std::string> >())
{
    _this->init(parent, name, default_index, restart_when_changed);
    _this->impl.init(possibilities);
}

template<>
Config<bool>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<bool>::type &default_value, bool restart_when_changed)
    : _this(new ConfigPrivate<bool>())
{
    _this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init();
}

template<>
Config<FilePath>::Config(RovizItem *parent, const std::string &name, const ConfigStorageType<FilePath>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed)
    : _this(new ConfigPrivate<FilePath>())
{
    _this->init(parent, name, default_value, restart_when_changed);
    _this->impl.init(filter, file_mode);
}

template<typename T>
Config<T> &Config<T>::operator=(Config<T> &&config)
{
    _this.reset(config._this.get());
    config._this.release();
    return *this;
}

template<typename T>
Config<T>::Config(Config &&config)
    : _this(config._this.get())
{
    config._this.release();
}

template<typename T>
typename ConfigStorageType<T>::type Config<T>::value()
{
    if(_this == nullptr)
        return typename ConfigStorageType<T>::type();

    std::lock_guard<std::mutex> lock(_this->mtx);

    return _this->val;
}

template<typename T>
bool Config<T>::changed()
{
    if(_this == nullptr)
        return false;

    std::lock_guard<std::mutex> lock(_this->mtx);

    return _this->changed;
}

template<typename T>
ConfigImplBase *Config<T>::getImplBase() const
{
    if(_this == nullptr)
        return nullptr;

    return &_this->impl;
}

INSTANTIATE_CONFIG
