#ifndef EXPORT_HANDLING_H
#define EXPORT_HANDLING_H

/** \mainpage roviz
 *
 * This is the combined documentation of the roviz framework and the
 * itemframework.
 *
 * The roviz framework is optimized to easily manipulate image/video streams
 * within the itemframework. It is completely decoupled from Qt and items that
 * are carefully written can therefore directly run on e.g. embedded hardware.
 * To achieve this portability, the base class of all items, RovizItem, is
 * written portably in pure C++. Depending on how the user compiles the program,
 * RovizItem gets a different base class. To use it with the itemframework, it
 * has RovizItemDevBase as the base class. This is the base class intended for
 * development. A more stripped down framework that would run in some kind of
 * production environment might be called RovizItemProdBase, but this class
 * heavily depends on the use case, which is why it doesn't exist yet. Items
 * that are for simulation/development purposes only, like test image generators
 * and the like, can be flagged as non-exportable by inheriting from
 * RovizItemNoExport, which provides the same interface, but won't be available
 * in production.
 *
 * Items also have a start/pause/stop mechanism that is triggered externally.
 * When an item is started, it gets its own thread where it can process all
 * the data. Pause will make the thread wait, but preserves the state the
 * item currently has. Stop will stop the thread and the item will fall
 * back to its initial state.
 *
 * There are trim values and configs to customize the item. Trim values are
 * nummeric values that can be adjusted at runtime. Adjusting them can for
 * example happen with a slider on a GUI (which RovizItemDevBase provides).
 * Configs on the other hand are not meant to change often. You have to open a
 * sepearate config window to change them (with RovizItemDevBase). The advantage
 * of them is that there are more data types available for configs. They can be
 * used for static values, like frame sizes, that you most likely only have to
 * set once and can forget about afterwards. Both, trim values and configs are
 * saved to the project by RovizItemDevBase using the itemframeworks
 * settingsScope.
 *
 * The roviz framework provides multiple types of streams that can for example
 * transport images or messages between items. Have a look here for an overview.
 *
 * To get started with roviz, have a look at \subpage getting_started.
 *
 * For more information, please visit this projects homepage: https://rdit-ch.github.io/roviz/
 */

// TODO Add this to the website
/*
 * BACKEND
 *
 * The roviz framework itself is basically only an API, it doesn't do very much
 * on its own. It defines a unified interface for the plugins and does some
 * very basic stuff like starting the threads. On the other side of the API,
 * we have a backend that can be controlled through the roviz layer. This
 * backend is where most of the background work happens, like showing images
 * or connecting items. The default backend connects the roviz layer with the
 * itemframework. But if you want to use a solution you developed within roviz
 * together with other applications, the itemframework might not be the best
 * backend. For that case, you can create another backend, that still uses
 * the same plugins, but instead of showing them with the itemframework, you
 * might want to visualize them with another application, or just run it
 * with a stripped down backend that only connects the items. Here again in
 * a bit more visual form:
 *
 * TODO: INSERT GRAPH HERE!
 *
 * We'll now see how to write a backend by using the cmdline backend as an
 * example:
 *
 * TODO: Implement that backend first...
 */

//#define ROVIZ_EXPORT

#ifdef ROVIZ_EXPORT
    #define ROVIZ_BASE_INCLUDE     "core/roviz_item_prod_base.h"
    #define ROVIZ_BASE_INCLUDE_P   "core/roviz_item_prod_base_p.h"
    #define ROVIZ_EXPORT_CLASS
    #define ROVIZ_INVOKABLE
    // Qt doesn't allow renaming O_OBJECT, because the moc isn't that smart
    #define Q_OBJECT
    #define ROVIZ_INIT_ITEM(name)
    #define OPENCV_PRESENT
#else
    #define ROVIZ_BASE_INCLUDE        "backend_dev/roviz_item_dev_base.h"
    #define ROVIZ_BASE_INCLUDE_P      "backend_dev/roviz_item_dev_base_p.h"
    #define ROVIZ_STREAM_BASE_INCLUDE "backend_dev/stream_dev_base.h"
    #define ROVIZ_CONFIG_IMPL_INCLUDE "backend_dev/config_impl_dev.h"
    #define ROVIZ_TRIM_BASE_INCLUDE   "backend_dev/trim_dev_base.h"
    #define ROVIZ_EXPORT_CLASS        Q_DECL_EXPORT
    #define ROVIZ_INVOKABLE           Q_INVOKABLE
    #define ROVIZ_INIT_ITEM(name)     {this->setImage(QImage(":/logo_"#name".png"));}
    #define QT_PRESENT
    #define OPENCV_PRESENT

    // Some color definitions for streams
    #define STREAM_COLOR_WHITE        Qt::white
    #define STREAM_COLOR_BLACK        Qt::black
    #define STREAM_COLOR_RED          Qt::red
    #define STREAM_COLOR_DARK_RED     Qt::darkRed
    #define STREAM_COLOR_GREEN        Qt::green
    #define STREAM_COLOR_DARK_GREEN   Qt::darkGreen
    #define STREAM_COLOR_BLUE         Qt::blue
    #define STREAM_COLOR_DARK_BLUE    Qt::darkBlue
    #define STREAM_COLOR_CYAN         Qt::cyan
    #define STREAM_COLOR_DARK_CYAN    Qt::darkCyan
    #define STREAM_COLOR_MAGENTA      Qt::magenta
    #define STREAM_COLOR_DARK_MAGENTA Qt::darkMagenta
    #define STREAM_COLOR_YELLOW       Qt::yellow
    #define STREAM_COLOR_DARK_YELLOW  Qt::darkYellow
    #define STREAM_COLOR_GRAY         Qt::gray
    #define STREAM_COLOR_DARK_GRAY    Qt::darkGray
    #define STREAM_COLOR_LIGHT_GRAY   Qt::lightGray

    // Needed by some modules and I don't want to wrap an #ifdef around all
    // of them.
    #include <QObject>

    // Select the appropriate base class for the items here
    class RovizItemDevBase;
    /**
     * @brief Backend of RovizItem
     *
     * \sa RovizItem
     */
    typedef RovizItemDevBase RovizItemBase;

    // Select the appropriate base class for streams here
    class StreamDevBase;
    /**
     * @brief Backend of Stream
     *
     * \sa Stream
     */
    typedef StreamDevBase StreamBase;

    // Select the appropriate implementation of the configs
    class ConfigImplDevBase;
    /**
     * @brief Backend of Config
     *
     * \sa Config
     */
    typedef ConfigImplDevBase ConfigImplBase;

    // Select the appropriate base class for the trim here
    class TrimDevBase;
    /**
     * @brief Backend of Trim
     *
     * \sa Trim
     */
    typedef TrimDevBase TrimBase;

    // Even though we use a #define below, this is still needed. Somehow.
    template<typename>
    class ConfigImplDev;

    // C++ won't allow us to use a typedef or using here because that would
    // impose restrictions, like not being allowed to instantiate the template
    // using the alias. So we have to do it the ugly way.
    #define ConfigImpl ConfigImplDev

#endif

#endif // EXPORT_HANDLING_H
