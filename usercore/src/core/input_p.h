#ifndef INPUT_P_H
#define INPUT_P_H

#include <list>
#include "core/export_handling.h"
#include "streams/stream_object.h"
#include "core/output_p.h"

class RovizItem;

/**
 * @brief Private part of the Input class
 *
 * This class is also used by the connection mechanism to push in new
 * StreamObject's into the item.
 *
 * \sa Input
 * \sa Output
 * \sa OutputPrivate
 */
class InputPrivate
{
public:
    RovizItem *item;
    std::list<StreamObject> objects;
    OutputPrivate::Connection connection;
    OutputPrivate *last_output;
    unsigned int current_seq_nr;

    InputPrivate();
    ~InputPrivate();

    /**
     * @brief Add an object to the input queue
     * @param obj The object
     *
     * Called by the connected output to add a new object to the queue of an input.
     *
     * \sa connect
     */
    void pushIn(StreamObject obj);

    /**
     * @brief Connect this input to an output
     * @param output The output
     *
     * Note: Connecting to a nullptr will disconnect this input.
     *
     * \sa disconnect
     * \sa pushIn
     * \sa OutputPrivate::connect
     */
    void connect(OutputPrivate *output);

    /**
     * @brief Disconnect this input
     *
     * \sa connect
     */
    void disconnect(void);
};

#endif // INPUT_P_H
