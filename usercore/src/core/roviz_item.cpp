
#include "core/roviz_item.h"
#include "core/roviz_item_p.h"

#include <thread>
#include <chrono>
#include <condition_variable>
#include "streams/all_streams.h"

RovizItem::RovizItem(std::string type_name)
    : RovizItemBase(type_name),
      _this(new RovizItemPrivate())
{
    _this->th = nullptr;
    _this->is_stopped = true;
    _this->is_paused = false;
}

RovizItem::~RovizItem()
{
    this->stop();
}

void RovizItem::starting()
{
}

bool RovizItem::wait()
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [this]{return !_this->is_paused || _this->is_stopped;});

    return !_this->is_stopped;
}

bool RovizItem::running() const
{
    return !_this->is_stopped && !_this->is_paused;
}

bool RovizItem::waitForCond(std::function<bool ()> cond)
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return (!_this->is_paused && cond()) || _this->is_stopped;});

    return !_this->is_stopped;
}

bool RovizItem::waitFor(std::function<bool ()> cond)
{
    while((_this->is_paused || !cond()) && !_this->is_stopped)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return !_this->is_stopped;
}

void RovizItem::wake() const
{
    _this->cond.notify_all();
}

std::mutex &RovizItem::mutex() const
{
    return _this->mtx;
}

Trim RovizItem::addTrim(std::string name, double default_value, double min, double max, std::function<void (double)> notifier_func)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, 0, false, notifier_func));
}

Trim RovizItem::addTrim(std::string name, double default_value, double min, double max, bool logarithmic)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, 0, logarithmic, [](double){}));
}

Trim RovizItem::addTrim(std::string name, double default_value, double min, double max, int steps, std::function<void (double)> notifier_func)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, steps, false, notifier_func));
}

Trim RovizItem::addTrim(std::string name, double default_value, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func)
{
    return Trim(this->getTrimImpl(name, default_value, min, max, steps, logarithmic, notifier_func));
}

Trim RovizItem::addTrim(std::string name, double default_value, double min, double max, double step_size, std::function<void (double)> notifier_func)
{
    // The cast is still needed because lround returns a long and not an int
    return Trim(this->getTrimImpl(name, default_value, min, max,
                                  static_cast<int>(std::lround((max - min) / step_size)),
                                  false, notifier_func));
}

void RovizItem::stopped()
{
}

void RovizItem::pause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = true;
}

void RovizItem::join()
{
    _this->th->join();
}

void RovizItem::unpause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = false;
    this->wake();
}

void RovizItem::start()
{
    this->starting();
    RovizItemBase::start();
    _this->is_stopped = false;
    _this->th = new std::thread(&RovizItem::thread, this);
}

void RovizItem::stop()
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
    this->stopped();
    RovizItemBase::stop();
}

template<class T>
Input<T> RovizItem::addInput(std::string name)
{
    return this->addInputBase<T>(name, this);
}

template<class T>
Output<T> RovizItem::addOutput(std::string name)
{
    return this->addOutputBase<T>(name);
}

template<>
Config<int> RovizItem::addConfig<int>(const std::string &name, const ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed)
{
    return Config<int>(this->getConfigImpl(name, default_value, min, max, restart_when_changed));
}

template<>
Config<double> RovizItem::addConfig<double>(const std::string &name, const ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed)
{
    return Config<double>(this->getConfigImpl(name, default_value, min, max, restart_when_changed));
}

template<>
Config<std::string> RovizItem::addConfig<std::string>(const std::string &name, const ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string &)> checker, bool restart_when_changed)
{
    return Config<std::string>(this->getConfigImpl(name, default_value, checker, restart_when_changed));
}

template<>
Config<std::list<std::string> > RovizItem::addConfig<std::list<std::string> >(const std::string &name, const ConfigStorageType<std::list<std::string> >::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed)
{
    return Config<std::list<std::string> >(this->getConfigImpl(name, default_index, possibilities, restart_when_changed));
}

template<>
Config<bool> RovizItem::addConfig<bool>(const std::string &name, const ConfigStorageType<bool>::type &default_value, bool restart_when_changed)
{
    return Config<bool>(this->getConfigImpl(name, default_value, restart_when_changed));
}

template<>
Config<FilePath> RovizItem::addConfig<FilePath>(const std::string &name, const ConfigStorageType<FilePath>::type &default_value, FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed)
{
    return Config<FilePath>(this->getConfigImpl(name, default_value, file_mode, filter, restart_when_changed));
}

INSTANTIATE_ROVIZ_ITEM
