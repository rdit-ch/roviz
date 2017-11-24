
#include "core/roviz_item.h"
#include "core/roviz_item_p.h"

#include <thread>
#include <chrono>
#include <condition_variable>
#include "streams/all_streams.h"

namespace roviz
{

Item::Item(std::string type_name)
    : ItemBase(type_name),
      _this(new ItemPrivate())
{
    _this->th = nullptr;
    _this->is_stopped = true;
    _this->is_paused = false;
}

Item::~Item()
{
    this->stop();
}

void Item::pre_thread()
{
}

void Item::stop()
{
    if(_this->th != nullptr)
    {
        _this->mtx.lock();
        _this->is_stopped = true;
        _this->is_paused = false;
        _this->mtx.unlock();
        _this->cond.notify_all();
        _this->th->join();
        delete _this->th;
        _this->th = nullptr;
    }
    this->post_thread();
    ItemBase::stop();
}

void Item::post_thread()
{
}

template<class T>
Input<T> Item::addInput(std::string name)
{
    return this->addInputBase<T>(name, this);
}

template<class T>
Output<T> Item::addOutput(std::string name)
{
    return this->addOutputBase<T>(name);
}

bool Item::waitForCond(std::function<bool ()> cond)
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return (!_this->is_paused && cond()) || _this->is_stopped;});

    return !_this->is_stopped;
}

bool Item::waitFor(std::function<bool ()> cond)
{
    while((_this->is_paused || !cond()) && !_this->is_stopped)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return !_this->is_stopped;
}

bool Item::wait()
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [this]{return !_this->is_paused || _this->is_stopped;});

    return !_this->is_stopped;
}

bool Item::running() const
{
    return !_this->is_stopped && !_this->is_paused;
}

void Item::wake() const
{
    _this->cond.notify_all();
}

std::mutex &Item::mutex() const
{
    return _this->mtx;
}

Trim Item::addTrim(std::string name, double default_value, double min, double max, std::function<void (double)> notifier_func)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, 0, false, notifier_func));
}

Trim Item::addTrim(std::string name, double default_value, double min, double max, bool logarithmic)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, 0, logarithmic, [](double){}));
}

Trim Item::addTrim(std::string name, double default_value, double min, double max, int steps, std::function<void (double)> notifier_func)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, steps, false, notifier_func));
}

Trim Item::addTrim(std::string name, double default_value, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, steps, logarithmic, notifier_func));
}

Trim Item::addTrim(std::string name, double default_value, double min, double max, double step_size, std::function<void (double)> notifier_func)
{
    // The cast is still needed because lround returns a long and not an int
    return Trim(this->getTrimImpl(name, default_value, min, max,
                                  static_cast<int>(std::lround((max - min) / step_size)),
                                  false, notifier_func));
}

template<>
Config<int> Item::addConfig<int>(const std::string &name, const ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed)
{
    return Config<int>(this->getConfigImpl(name, default_value, min, max, restart_when_changed));
}

template<>
Config<double> Item::addConfig<double>(const std::string &name, const ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed)
{
    return Config<double>(this->getConfigImpl(name, default_value, min, max, restart_when_changed));
}

template<>
Config<std::string> Item::addConfig<std::string>(const std::string &name, const ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string &)> checker, bool restart_when_changed)
{
    return Config<std::string>(this->getConfigImpl(name, default_value, checker, restart_when_changed));
}

template<>
Config<std::vector<std::string> > Item::addConfig<std::vector<std::string> >(const std::string &name, const ConfigStorageType<std::vector<std::string> >::type &default_index, const std::vector<std::string> &possibilities, bool restart_when_changed)
{
    return Config<std::vector<std::string> >(this->getConfigImpl(name, default_index, possibilities, restart_when_changed));
}

template<>
Config<bool> Item::addConfig<bool>(const std::string &name, const ConfigStorageType<bool>::type &default_value, bool restart_when_changed)
{
    return Config<bool>(this->getConfigImpl(name, default_value, restart_when_changed));
}

template<>
Config<FilePath> Item::addConfig<FilePath>(const std::string &name, const ConfigStorageType<FilePath>::type &default_value, FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed)
{
    return Config<FilePath>(this->getConfigImpl(name, default_value, file_mode, filter, restart_when_changed));
}

void Item::start()
{
    this->pre_thread();
    ItemBase::start();
    _this->is_stopped = false;
    _this->th = new std::thread(&Item::thread, this);
}

void Item::pause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = true;
}

void Item::join()
{
    _this->th->join();
}

void Item::unpause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = false;
    this->wake();
}

#define INSTANTIATE_ROVIZ_ITEM(T) \
    template Input<T > Item::addInput<T >(std::string name); \
    template Output<T > Item::addOutput<T >(std::string name); \
    template Config<int> Item::addConfig<int>(const std::string &name, const typename ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed); \
    template Config<double> Item::addConfig<double>(const std::string &name, const typename ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed); \
    template Config<std::string> Item::addConfig<std::string>(const std::string &name, const typename ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed); \
    template Config<std::vector<std::string> > Item::addConfig<std::vector<std::string> >(const std::string &name, const typename ConfigStorageType<std::vector<std::string> >::type &default_index, const std::vector<std::string> &possibilities, bool restart_when_changed); \
    template Config<bool> Item::addConfig<bool>(const std::string &name, const typename ConfigStorageType<bool>::type &default_value, bool restart_when_changed); \
    template Config<FilePath> Item::addConfig<FilePath>(const std::string &name, const typename ConfigStorageType<FilePath>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed);

ROVIZ_DO_FOR_ALL_STREAMS(INSTANTIATE_ROVIZ_ITEM)

}
