#ifndef TRIM_DEV_BASE_P_H
#define TRIM_DEV_BASE_P_H

#include <functional>
#include <string>

class QLayout;
class QSlider;
class RovizItem;

/**
 * @brief Private part of TrimDevBase
 *
 * \sa TrimDevBase
 */
class TrimDevBasePrivate
{
public:
    RovizItem *item;
    double val;
    QLayout *main_layout;
    QSlider *main_slider;
    std::string name;
    bool loaded;

    /**
     * @brief Load the current state of the slider from the config.
     */
    void load(void);
};

#endif // TRIM_DEV_BASE_P_H
