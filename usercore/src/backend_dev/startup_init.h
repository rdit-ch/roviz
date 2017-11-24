#ifndef STARTUP_INIT_H
#define STARTUP_INIT_H

#include <QObject>

namespace roviz
{

/**
 * @brief This class assigns each stream a color so they are easily
 * distinguishable.
 *
 * You can change the colors of existing streams or add new streams
 * by modifying the color table in 'backend_dev/startup.cpp'.
 *
 * \sa StreamObject
 */
class StartupInit : public QObject
{
Q_OBJECT

public:
    /**
     * @brief This function is called exactly once at application
     * startup.
     */
    static void init(void);
};

}

#endif // STARTUP_INIT_H
