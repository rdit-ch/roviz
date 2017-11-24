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
 * To achieve this portability, the base class of all items, Item, is
 * written portably in pure C++. Depending on how the user compiles the program,
 * Item gets a different base class and a different backend. Currently there
 * are two supported backends: Dev and Cmdline. Dev is the default itemframework
 * implementation mainly intended for devlopment and testing of solutions. The
 * Cmdline backend on the other hand has no graphical interface anymore and is
 * trimmed for performance. It parses a project file that was created with the
 * Dev backend and runs it in a portable, Qt-less and fast environment.
 *
 * Items also have a start/pause/stop mechanism that is triggered externally.
 * When an item is started, it gets its own thread where it can process all
 * the data. Pause will make the thread wait, but preserves the state the
 * item currently has. Stop will stop the thread and the item will fall
 * back to its initial state.
 *
 * There are trim values and configs to customize the item. Trim values are
 * nummeric values that can be adjusted at runtime. Adjusting them can for
 * example happen with a slider on a GUI (which the Dev backend provides).
 * Configs on the other hand are not meant to change often. You have to open a
 * sepearate config window to change them (with the Dev backend). The advantage
 * of them is that there are more data types available for configs. They can be
 * used for static values, like frame sizes, that you most likely only have to
 * set once and can forget about afterwards. Both, trim values and configs are
 * saved to the project by the Dev backend using the itemframeworks
 * settingsScope.
 *
 * The roviz framework provides multiple types of streams that can for example
 * transport images or messages between items. See StreamObject.
 *
 * To get started with roviz, have a look at \subpage getting_started.
 *
 * For more information, please visit this projects homepage: https://rdit-ch.github.io/roviz/
 */

// This is needed because otherwise, the symbols wouldn't be evaluated first
#define CONCAT_(A, B)  A ## B
#define CONCAT(A, B)   CONCAT_(A, B)

// It doesn't matter what numbers those have, as long as they're unique.
// This is needed, because we need something to compare backends with
// eachother and plain symbols won't work.
#define ROVIZ_BACKEND_Dev      0
#define ROVIZ_BACKEND_Cmdline  1

#define ROVIZ_BACKEND          CONCAT(ROVIZ_BACKEND_, ROVIZ_SELECTED_BACKEND)

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Cmdline
    // We don't use a typedef here because typedefs can't be friends (used in Input/Output)
    #define ItemBase  ItemBaseCmdline

    #define ROVIZ_BASE_INCLUDE    "backend_cmdline/roviz_item_base_cmdline.h"
    #define ROVIZ_INVOKABLE
    // Qt doesn't allow renaming O_OBJECT, because the moc isn't that smart
    #define Q_OBJECT
    #define ROVIZ_INIT_ITEM(name)
    #define OPENCV_PRESENT
    #define DECLARE_STREAM_OBJECT(T)

#elif ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    // We don't use a typedef here because typedefs can't be friends (used in Input/Output)
    #define ItemBase  ItemBaseDev

    #define ROVIZ_BASE_INCLUDE     "backend_dev/roviz_item_base_dev.h"
    #define ROVIZ_INVOKABLE        Q_INVOKABLE
    #define ROVIZ_INIT_ITEM(name)  {this->setImage(QImage(":/logo_"#name".png"));}
    #define QT_PRESENT
    #define OPENCV_PRESENT

    // Has to be used on all declarations of stream object
    #define DECLARE_STREAM_OBJECT(T)  Q_DECLARE_METATYPE(T)

    // Needed by some modules and I don't want to wrap an #ifdef around all
    // of them.
    #include <QObject>

    // For simulation-only items
    namespace roviz
    {
        class Item;
        typedef Item ItemNoExport;
    }

#else
    #error It seems like you did not select a proper backend
#endif

#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
  #ifdef __GNUC__
    #define ROVIZ_EXPORT_CLASS __attribute__ ((dllexport))
  #else
    #define ROVIZ_EXPORT_CLASS __declspec(dllexport)
  #endif
#else
  #if __GNUC__ >= 4
    #define ROVIZ_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define ROVIZ_EXPORT_CLASS
  #endif
#endif

// General purpose macros
#define COPY_DEFAULT(T)  public: T(const T &) = default; T &operator=(const T &) = default;
#define COPY_DELETE(T)   public: T(const T &) = delete;  T &operator=(const T &) = delete;
#define MOVE_DEFAULT(T)  public: T(T &&)      = default; T &operator=(T &&)      = default;
#define MOVE_DELETE(T)   public: T(T &&)      = delete;  T &operator=(T &&)      = delete;

#endif // EXPORT_HANDLING_H
