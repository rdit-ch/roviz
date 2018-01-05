#ifndef OUTPUT_P_H
#define OUTPUT_P_H

#include <functional>
#include <mutex>
#include <list>
#include "core/export_handling.h"
#include "streams/stream_object.h"

class InputPrivate;

/**
 * @brief Private part of the Ouput class
 *
 * This class is also used by the connection mechanism to connect to inputs.
 */
class ROVIZ_EXPORT OutputPrivate
{
public:
    typedef std::list<std::function<void (StreamObject)> >::const_iterator Connection;

    std::list<std::function<void (StreamObject)> > pushInFuncs;
    std::list<InputPrivate*> connected_inputs;
    RovizItem *parent_item;
    unsigned int next_new_seq_nr;

    OutputPrivate() = default;
    ~OutputPrivate();

    /**
     * @brief Connects an input to this output
     * @param in The input to connect
     * @param fn The pushIn function of that input
     * @return An object representing this connection
     *
     * \sa disconnect
     */
    Connection connect(InputPrivate *in, std::function<void (StreamObject)> fn);

    /**
     * @brief Disconnet an input from this output
     * @param in The input to disconnect
     * @param fn The connection
     *
     * \sa connect
     */
    void disconnect(InputPrivate *in, Connection conn);

private:
    std::mutex mtx;
};

#endif // OUTPUT_P_H
