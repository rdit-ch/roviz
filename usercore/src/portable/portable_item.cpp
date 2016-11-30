
#include "portable/portable_item.h"
#include "portable/portable_item_p.h"

PortableItem::PortableItem(std::string typeName)
    : PortableItemBase(typeName),
      _this(new PortableItemPrivate(this))
{
    _this->th = nullptr;
    _this->is_stopped = true;
    _this->is_paused = false;
}

PortableItem::~PortableItem()
{
    this->stop();
    for(auto ent : _this->img_in_queue)
        delete ent.second;
    _this->img_in_queue.clear();
}

void PortableItem::starting()
{
}

PortableImage PortableItem::nextImage(void *input)
{
    return _this->img_in_queue[input]->next();
}

PortableImage PortableItem::newestImage(void *input)
{
    return _this->img_in_queue[input]->newest();
}

bool PortableItem::waitForImage(void *input)
{
    // Give other threads a chance too
    std::this_thread::yield();

    if(_this->img_in_queue.find(input) == _this->img_in_queue.end())
        return false;

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return _this->img_in_queue[input]->available() || _this->is_stopped;});

    return !_this->is_stopped;
}

bool PortableItem::wait()
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [this]{return !_this->is_paused || _this->is_stopped;});

    return !_this->is_stopped;
}

bool PortableItem::running()
{
    return !_this->is_stopped && !_this->is_paused;
}

bool PortableItem::waitForCond(std::function<bool ()> cond)
{
    // Give other threads a chance too
    std::this_thread::yield();

    std::unique_lock<std::mutex> lock(_this->mtx);
    _this->cond.wait(lock, [&]{return (!_this->is_paused && cond()) || _this->is_stopped;});

    return !_this->is_stopped;
}

bool PortableItem::waitFor(std::function<bool ()> cond)
{
    while((_this->is_paused || !cond()) && !_this->is_stopped)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return !_this->is_stopped;
}

void PortableItem::wake()
{
    _this->cond.notify_all();
}

std::mutex &PortableItem::mutex()
{
    return _this->mtx;
}

void PortableItem::trimChanged(void *, double )
{
}

void PortableItem::addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker)
{
    PortableItemBase::addConfig(name, value, checker);
}

void PortableItem::addConfig(std::string name, int *value, std::function<int (int)> checker)
{
    PortableItemBase::addConfig(name, value, checker);
}

void PortableItem::addConfig(std::string name, double *value, std::function<double (double)> checker)
{
    PortableItemBase::addConfig(name, value, checker);
}

void PortableItem::addConfig(std::string name, bool *value)
{
    PortableItemBase::addConfig(name, value);
}

void PortableItem::addConfig(std::string name, std::vector<std::string> possibilities, int *index)
{
    PortableItemBase::addConfig(name, possibilities, index);
}

void *PortableItem::addMessageOutput(std::string name)
{
    return PortableItemBase::addMessageOutput(name);
}

void *PortableItem::addMessageInput(std::string name)
{
    return PortableItemBase::addMessageInput(name);
}

void PortableItem::outputMessage(void *output, Message message)
{
    PortableItemBase::outputMessage(output, message);
}

void PortableItem::newMessageReceived(void *, Message)
{
}

void PortableItem::stopped()
{
}

void *PortableItem::addImageInput(std::string name)
{
    void *in;

    in = PortableItemBase::addImageInput(name);
    _this->img_in_queue[in] = new ImageQueue();

    return in;
}

void *PortableItem::addImageOutput(std::string name)
{
    return PortableItemBase::addImageOutput(name);
}

void PortableItem::pushImageOut(PortableImage img, void *output)
{
    PortableItemBase::pushImageOut(img, output);
}

void *PortableItem::addTrim(std::string name, int min, int max)
{
    return PortableItemBase::addTrim(name, min, max);
}

void *PortableItem::addTrim(std::string name, double min, double max, int steps)
{
    return PortableItemBase::addTrim(name, min, max, steps);
}

double PortableItem::trimValue(void *trim)
{
    return PortableItemBase::trimValue(trim);
}

void PortableItem::pause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = true;
}

void PortableItem::unpause()
{
    std::lock_guard<std::mutex> g(_this->mtx);

    _this->is_paused = false;
    this->wake();
}

void PortableItem::pushImageIn(PortableImage img, void *input)
{
    if(_this->img_in_queue.size() < MAX_QUEUE_SIZE)
    {
        _this->img_in_queue[input]->push(img);
        _this->cond.notify_all();
    }
}

void PortableItem::start()
{
    this->starting();
    AbstractRobotItem::start();
    _this->is_stopped = false;
    _this->th = new std::thread(&PortableItem::thread, this);
}

void PortableItem::stop()
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
    PortableItemBase::stop();
}
