#ifndef INPUT_H
#define INPUT_H

#include "core/export_handling.h"
#include "core/input_p.h"

namespace roviz
{

class Item;

/**
 * @brief Represents the input of an item
 *
 * The input will receive StreamObject's that other items, that are connected
 * to this input, emit. The template type of this class has to be a valid
 * StreamObject implementation.
 *
 * \sa Output
 */
template<class T>
class ROVIZ_EXPORT Input
{
// We have to directly access '_this' from the Item bases,
// there is no way around this at the moment
friend class ItemBase;

COPY_DELETE(Input)
MOVE_DEFAULT(Input)

public:
    Input() = default;
    ~Input() = default;

    explicit Input(Item *item);

    /**
     * @brief Returns the next object in the input queue
     * @param input The input handle returned from addInput()
     * @return The next object in the input queue
     *
     * \sa addInput
     * \sa newest
     */
    T next(void);

    /**
     * @brief Returns the newest object in the input queue
     * @param input The input handle returned from addInput()
     * @return Returns the newest object in the input queue
     *
     * All older objects in the input queue are discarded.
     *
     * \sa addInput
     * \sa next
     */
    T newest(void);

    /**
     * @brief Wait until an object is available at the input
     * @param input The input handle returned from addInput()
     * @return true - New object is available
     *         false - The item was stopped, the thread _HAS TO_ exit
     *
     * This function should be used by most (image processing) items to ensure
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
    bool waitForInput(void);

private:
    std::unique_ptr<InputPrivate> _this;
};

}

#endif // INPUT_H
