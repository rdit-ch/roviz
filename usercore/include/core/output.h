#ifndef OUTPUT_H
#define OUTPUT_H

#include <memory>
#include "core/export_handling.h"
#include "core/output_p.h"

namespace roviz
{

class Item;

/**
 * @brief Represents the output of an item
 *
 * The template type of this class has to be a valid StreamObject implementation.
 *
 * \sa Input
 */
template<class T>
class ROVIZ_EXPORT Output
{
// We have to directly access '_this' from the RovizItem bases,
// there is no way around this at the moment
friend class ItemBase;

COPY_DELETE(Output)
MOVE_DEFAULT(Output)

public:
    Output();
    ~Output() = default;

    /**
     * @brief Pushes out a Stream object
     * @param obj A StreamObject
     *
     * Forwards a StreamObject to all connected inputs.
     *
     * __VERY IMPORTANT:__ Do NOT modify the corresponding mutable object of 'obj'
     * after this function call! This function will take ownership of 'obj', any
     * modifications to it would propagate to the connected inputs, which might
     * lead to race conditions and horrible failures!
     */
    void pushOut(T obj);

private:
    std::unique_ptr<OutputPrivate> _this;
};

}

#endif // OUTPUT_H
