---
---

# What backends are and how to create your own

The roviz framework itself is basically only an API, it doesn't do very much on its own. It defines a unified interface for the plugins and does some very basic stuff like starting the threads. On the other side of the API, we have a backend that can be controlled through the roviz layer. This backend is where most of the background work happens, like showing images or connecting items.

There are currently two backends:

 - `Dev`: This is the default backend and uses the [itemframework](https://github.com/rdit-ch/itemframework). Its purpose it to easily connect items and adjust trims.
 - `Cmdline`: Once your application works, you can switch to the `Cmdline` backend. This is a very stripped down backend that removes all GUIs, it doesn't even need Qt to run. It parses a project file created with the `Dev` backend, connects the items and runs the threads. Nothing more. With that backend, you can then run your application with a much higher performance.

In case those backends are not enough for you, say if you for example would like to integrate roviz in another application, you can create you own backend. For that, you have to implement at least 3 classes:

 - A base class for [`RovizItem`](https://shadowigor.github.io/roviz-docs/api/classRovizItem)
 - An implementation of the configs ([`ConfigImpl`](https://shadowigor.github.io/roviz-docs/api/classConfigImpl))
 - An implementation of the trims ([`TrimImpl`](https://shadowigor.github.io/roviz-docs/api/classTrimImpl))

As the `Cmdline` backend very minimal, I'd suggest you to look at it's implementation to see how these classes work.

Some important notes (assuming your backend is called `YourBackend`:
 - You have to add a couple of things to `usercore/include/core/export_handling.h`:
   - A `#define` for `ROVIZ_BACKEND_YourBackend`. This is used to determine which backend is currently used at some points. It has to be some random number that is not used already. (Don't capitalize `YourBackend`!)
   - A `#define` for `RovizItemBase` that points to your base class for [`RovizItem`](https://shadowigor.github.io/roviz-docs/api/classRovizItem)
   - A `#define` for `ROVIZ_BASE_INCLUDE` pointing to the path to the header of you [`RovizItem`](https://shadowigor.github.io/roviz-docs/api/classRovizItem) base class
   - A `#define` (can also be empty if it's not used) for the following:
     - `ROVIZ_INVOKABLE` The `Dev` backend needs this to be in front of to constructors of plugin items so it can call them (`Q_INVOKABLE`).
     - `ROVIZ_INIT_ITEM(name)` Initializes the item with the name `name`
     - `QT_PRESENT` in case Qt is available
     - `CV_PRESENT` in case OpenCV is available
     - `DECLARE_STREAM_OBJECT(T)` Needed by the `Dev` backend to make stream objects known to Qt's meta object system
     - `Q_OBJECT` in case you're not using Qt, because the items have to be `QObject`s for the `Dev` backend
 - In the `usercore/usercore.pro` file, add a `equals(BACKEND, "YourBackend") {` section and add all your backend specific source files within that block. (Note: The opening brace has to be on the same line as the `equals` statement)
 - You might also want to look at `usercore/usercore.pri` and add some general purpose configs (or use the same as the Cmdline backend)
 - The usercore is only a library, you might also need a starter that loads the plugins and starts the operation. You should add the subdir of the starter in the `roviz.pro` file, again in a `equals(BACKEND, "YourBackend") {` block.
 - To compile roviz with your new backend, run `qmake` with the additional argument `BACKEND=YourBackend` (again, don't capitalize `YourBackend`!)
