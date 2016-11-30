#ifndef PORTABLEITEM_H
#define PORTABLEITEM_H

/**
 * \defgroup robot_framework Robot Framework
 *
 * The robot framework is optimized to easily manipulate image/video streams
 * within traviz. It is completely decoupled from Qt and items that are
 * carefully written can therefore directly run on hardware. To achieve
 * this portability, the base class of all items, PortableItem,
 * is written portably in pure C++. Depending on how the user compiles the
 * program, PortableItem gets a different base class. To use it
 * in traviz, it has AbstractRobotItem as the base class.
 * AbstractRobotItem binds the interface to traviz, handles the
 * connections traviz makes, visualizes the data and acts as a bridge
 * between Qt and standard C++. In the future, there will also be other base
 * classes available for PortableItem, for example one that
 * connects the items via ROS to make them available on embedded platforms.
 * Items that are meant to be exportable, should therefore be written in
 * pure C++. Items that are for simulation purposes only can be flagged as
 * non-exportable by inheriting from NonPortableItem.
 * NonPortableItem provides the same interface as
 * PortableItem.
 *
 * Items also have a start/pause/stop mechanism that is triggered externally.
 * When an item is started, it gets its own thread where it can process all
 * the data. Pause will make the thread wait, but preserves the state the
 * item currently has. Stop will stop the thread and the item will fall
 * back to its initial state.
 *
 * There are trim values and configs to customize the item. Trim values are
 * nummeric values that can be adjusted at runtime. Adjusting them can for
 * example happen with a slider on a GUI. Configs on the other hand are not
 * meant to change often. Everytime a config changes, the item is
 * automatically restarted. The advantage of them, is that there are more
 * data types available for configs. They can be used for static values,
 * like frame sizes, that you most likely only have to set once and can
 * forget about afterwards.
 *
 * The robot framework also provides message streams for control data. Once
 * the desired information is extracted from images, these messages could
 * be used to control parts of the robot. They could also be a second
 * source of sensor information that isn't as ressource intensive as images.
 *
 * If you want to write an item using the robot framework, have a look at
 * PortableItem to get started.
 */

/**
 * \defgroup robot_plugins Robot Plugins
 *
 * Plugins for the robot framework.
 *
 * \ingroup robot_framework
 */

// TODO If one thread alone can't handle all data, spawn more threads
// to already start processing the next images as soon as they arrive.

#include <list>
#include <map>
#include <thread>
#include <condition_variable>
#include <functional>
#include <chrono>
#include "portable_item_global.h"
#include "portable_image.h"
#include "portable/image_queue.h"

class PortableItemPrivate;

// Include the appropriate base class
#include PORTABLE_BASE_INCLUDE

#define MAX_QUEUE_SIZE 32

/**
 * @brief Base class for all items that use the robot framework.
 *
 * All items using the robot framework have to inherit from this class. They
 * have to at least implement thread(). This function will run in a seperate
 * thread and can process the image data.
 *
 * \sa AbstractRobotItem
 * \sa NonPortableItem
 * \sa PortableItemBase
 * \ingroup robot_framework
 */
class PORTABLE_EXPORT_CLASS PortableItem : public PortableItemBase
{
    // The moc won't allow a portable name
    Q_OBJECT

public:
    /**
     * @param typeName The name of the item
     */
    explicit PortableItem(std::string typeName);

    virtual ~PortableItem();

protected:
    /**
     * @brief Called, when the thread is about to start
     *
     * Use this function to reset, clear and initialize everything that might
     * change during runtime. After the call to this function, the item has
     * to be in a clean, fresh state. The item is not allowed to have any
     * information of the previous "session" or thread run left. That would
     * defy the purpose of the start/stop mechanism. The inputs/outputs are
     * preserved, you can set them in the constructor. The thread doesn't run
     * yet at this point.
     *
     * \sa stopped
     */
    virtual void starting(void);

    /**
     * @brief Main thread of the item
     *
     * This function will be executed in a different thread and you can
     * process the image data in here.
     *
     * \sa starting
     * \sa stopped
     */
    virtual void thread(void) = 0;

    /**
     * @brief Stop thread operation
     *
     * __Important:__ You have to call this function in the destructor, otherwise
     * the thread might still run after destruction of the members, even if it
     * is called in the base class destructor.
     *
     * \sa stopped
     * \sa starting
     */
    void stop(void) override;

    /**
     * @brief Called after the thread stopped
     *
     * Called _after_ the thread stopped. You can do some cleanup here if you
     * like.
     *
     * \sa starting
     */
    virtual void stopped(void);

    /**
     * @brief Returns the next image in the input queue
     * @param input The input handle returned from addImageInput()
     * @return The next image in the input queue
     *
     * \sa addImageInput
     * \sa newestImage
     */
    PortableImage nextImage(void *input);

    /**
     * @brief Returns the newest image in the input queue
     * @param input The input handle returned from addImageInput()
     * @return Returns the newest image in the input queue
     *
     * All older images in the input queue are discarded.
     *
     * \sa addImageInput
     * \sa nextImage
     */
    PortableImage newestImage(void *input);

    /**
     * @brief Wait until an image is available at the input
     * @param input The input handle returned from addImageInput()
     * @return true - New image is available
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function should be used by most image processing items to ensure
     * the start/pause/stop mechanism works.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa waitFor
     * \sa wait
     * \sa running
     */
    bool waitForImage(void *input);

    /**
     * @brief Sleep until a condition comes true
     * @param cond Condition to wait for
     * @return true - The condition returned true
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function could be used by image sources that have to wait for
     * hardware events. It will wait until the cond function returns true.
     * The cond function will be called periodically. It might happen, that
     * the thread keeps sleeping and doesn't notice that the condition
     * changed. Use wake() from an event handler or interrupt or something
     * similar to ensure the thread checks the condidion again. If this is not
     * possible, use the less efficient waitFor() instead. This function
     * will aquire the mutex returned by mutex() while executing cond.
     * Make sure you only manipulate the condition while holding that mutex.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa wake
     * \sa mutex
     * \sa waitForImage
     * \sa wait
     * \sa running
     */
    bool waitForCond(std::function<bool (void)> cond);

    /**
     * @brief Wait until a condition comes true
     * @param cond Condition to wait for
     * @return true - The condition returned true
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function could be used by image sources that have to wait for
     * hardware events. It will wait until the cond function returns true.
     * The cond function will be called periodically. Unlike waitForCond(),
     * this functions guarantees that the condition is evatluated
     * periodically. This function will aquire the mutex returned by mutex()
     * while executing cond. Make sure you only manipulate the condition while
     * holding that mutex.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa wake
     * \sa mutex
     * \sa waitForImage
     * \sa wait
     * \sa running
     */
    bool waitFor(std::function<bool (void)> cond);

    /**
     * @brief Wait if the item is paused
     * @return true - No need to wait
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function could be used for image sources that don't need a
     * condidion to be matched to generate an image.
     *
     * This function implements the pause/stop mechanism. It doesn't return
     * as long as the item is paused and returns false if it is stopped. It
     * is important that the thread exits when this happens!
     *
     * \sa waitForImage
     * \sa waitFor
     * \sa running
     */
    bool wait(void);

    /**
     * @brief Check if the thread is running
     * @return true, if the thread is running
     *         false, if the thread is paused or stopped
     *
     * This function does _not_ handle start/pause/stop events itself. It
     * could be used in event handlers, to check, whether they have to
     * process this event, because it doesn't make sense to do that if the
     * thread isn't running anyway. It normally doesn't make much sense to
     * call this function from the thread() function. Use wait() instead
     * for that.
     *
     * \sa waitForImage
     * \sa waitFor
     * \sa wait
     */
    bool running(void) override;

    /**
     * @brief Wake the possibly waiting thread
     *
     * If you know the thread is waiting for a condidion and e.g. an event
     * handler sees that the condidion has changed, it's a good idea to
     * notify the thread and wake it up.
     *
     * \sa waitFor
     */
    void wake(void);

    /**
     * @brief Mutex that waitFor() locks to check the condidion
     * @return Mutex that waitFor() locks to check the condidion
     *
     * Only change the condition waitFor() is waiting for while holding this
     * mutex!
     *
     * \sa waitFor
     */
    std::mutex &mutex(void);

    /**
     * @brief Add an image input
     * @param name Name of the input
     * @return Handle to that input
     *
     * \sa addImageOutput
     */
    void *addImageInput(std::string name) override;

    /**
     * @brief Add an image output
     * @param name Name of the output
     * @return Handle to that output
     *
     * \sa addImageInput
     * \sa pushImageOut
     */
    void *addImageOutput(std::string name) override;

    /**
     * @brief Send an image out through an output
     * @param img The image
     * @param output The output handle returned from addImageOutput()
     *
     * This function is completely thread safe, you can call it from
     * thread() of any other function, like e.g. an event handler.
     *
     * \sa addImageOutput
     */
    void pushImageOut(PortableImage img, void *output) override;

    /**
     * @brief Add a message output
     * @param name Name of the output
     * @return Handle to that output
     *
     * \sa outputMessage
     * \sa addMessageInput
     */
    void *addMessageOutput(std::string name) override;

    /**
     * @brief Add a message input
     * @param name Name of the input
     * @return Handle to that input
     *
     * \sa newMessageReceived
     * \sa addMessageOutput
     */
    void *addMessageInput(std::string name) override;

    /**
     * @brief Write a message to the output
     * @param output The output handle returned from addMessageOutput()
     * @param message The message to send
     *
     * You have to manually set the type of each message by altering the 'type' field.
     */
    void outputMessage(void *output, Message message) override;

    /**
     * @brief Called when a new message arrived at an input
     * @param input The input that received the message
     * @param message The message that was received
     */
    virtual void newMessageReceived(void *input, Message message) override;

    /**
     * @brief Add a trim value
     * @param name Name of the value
     * @param min Minimum value
     * @param max Maximum value
     * @return Handle to the trim value
     *
     * Adds a trim value with whole-number steps. See addTrim().
     *
     * \sa addTrim
     * \sa trimValue
     * \sa trimChanged
     */
    void *addTrim(std::string name, int min, int max) override;

    /**
     * @brief Add a trim value
     * @param name Name of the value
     * @param min Minimum value
     * @param max Maximum value
     * @param steps Number of steps between min and max
     * @return Handle to the trim value
     *
     * A trim value is a value, that can be adjusted (trimmed) at runtime. The
     * user can changed it e.g. through a slider on a GUI.
     */
    void *addTrim(std::string name, double min, double max, int steps) override;

    /**
     * @brief Get the value of a trim value
     * @param trim Handle to the trim value returned from addTrim()
     * @return The value the trim value currently has
     */
    double trimValue(void *trim) override;

    /**
     * @brief Called, when the trim value changed
     * @param trim Handle to the trim value returned from addTrim()
     * @param value New value that the trim value has
     *
     * This function will be called in the main thread, _not_ the thread that
     * the thread() function lives in.
     */
    virtual void trimChanged(void *trim, double value) override;

    /**
     * @brief Add a string config
     * @param name Name of the config
     * @param value Pointer to the value that will be updated with the new config
     * @param checker Function that checks, whether the input is valid or not
     */
    void addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker = [](std::string a){return a;}) override;

    /**
     * @brief Add an int config
     * @param name Name of the config
     * @param value Pointer to the value that will be updated with the new config
     * @param checker Function that checks, whether the input is valid or not
     *
     * __Important:__ The data _value_ points to is only valid during the started() method!
     */
    void addConfig(std::string name, int *value, std::function<int (int)> checker = [](int a){return a;}) override;

    /**
     * @brief Add a double config
     * @param name Name of the config
     * @param value Pointer to the value that will be updated with the new config
     * @param checker Function that checks, whether the input is valid or not
     *
     * __Important:__ The data _value_ points to is only valid during the started() method!
     */
    void addConfig(std::string name, double *value, std::function<double (double)> checker = [](double a){return a;}) override;

    /**
     * @brief Add a bool config
     * @param name Name of the config
     * @param value Pointer to the value that will be updated with the new config
     *
     * __Important:__ The data _value_ points to is only valid during the started() method!
     */
    void addConfig(std::string name, bool *value) override;

    /**
     * @brief Add a config with a defined list of choices
     * @param name Name of the config
     * @param possibilities List of all possible values
     * @param index Pointer to the index variable that will we updated with the currently active list entry index
     *
     * __Important:__ The data _index_ points to is only valid during the started() method!
     */
    void addConfig(std::string name, std::vector<std::string> possibilities, int *index) override;

private:
    std::unique_ptr<PortableItemPrivate> _this;

    /**
     * @name Internal interface functions
     *
     * These functions are not visible to child classes. They are part of the
     * interface that is visible to the base class. The base class can call
     * them to interact with this class. They are marked as override so the
     * base class is forced to implement them as virtual functions. Otherwise,
     * the base class could not even see them.
     */
    ///@{

    /**
     * @brief Add an image to the input queue
     * @param img The image
     * @param input The input handle returned from addImageInput()
     *
     * Called by the base class to add a new image to the queue of an input.
     */
    void pushImageIn(PortableImage img, void *input) override;

    /**
     * @brief Pause execution
     *
     * Pauses the operation of the item, but does not reset it.
     *
     * \sa unpause
     */
    void pause(void) override;

    /**
     * @brief Resume execution
     *
     * Resumes execution after a call to pause()
     *
     * \sa pause
     */
    void unpause(void) override;

    /**
     * @brief Start execution
     *
     * Starts the thread and the processing of data
     *
     * \sa stop
     * \sa pause
     */
    void start(void) override;
    ///@}
};

#endif // PORTABLEITEM_H
