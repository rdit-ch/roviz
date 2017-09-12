---
---

# What streams are and how to create your own

Streams describe the connection between two items. For example, the main stream of the roviz framework is the image stream. It transports objects of type [Image](https://shadowigor.github.io/roviz-docs/api/classImage.html){:target="_blank"} from one item to another. If you would like to transport your own type with a stream, all you have to do is the following:

1. Create a class for your transport type  
2. Make it publically inherit from [StreamObject](https://shadowigor.github.io/roviz-docs/api/classStreamObject.html){:target="_blank"} (`streams/stream_object.h`)  
3. Add a `static QWidget *initWidget(OutputPrivate *out);` function  
   This function should return a pointer to a [QWidget](https://doc.qt.io/qt-5/qwidget.html){:target="_blank"} that will be displayed in the shared window for this stream. If you do not want do display anything, just return `nullptr`. Make sure you enclose it with a `#ifndef ROVIZ_BACKEND == ROVIZ_BACKEND_Dev ... #endif` block, because that part only works with the 'Dev' backend. The `out` parameter refers to the output that will be associated with this stream. You should should use it to call `OutputPrivate::connect` to get notified when new data should be displayed (see [OutputPrivate::connect](https://shadowigor.github.io/roviz-docs/api/classOutputPrivate.html#a9505e803f1853948a2b7c995b71986fd)).
4. Add your class to `usercore/include/streams/template_decl.h`  
   There are some functions in the core that accept stream types as template parameters. We have to ensure that those functions are instantiated with every stream type. This is done by macros, all you have to do is to add your class to the `DO_FOR_ALL_STREAMS` macro in `usercore/include/core/template_decl.h`. Also make sure that you declare your class in that file (`class YourClass;`), just like the existing streams do.
5. Choose a color  
   Every stream is identified by a connection color. You can set that color by adding your class to the color table in the `usercore/src/backend_dev/startup_init.cpp` file. The color is a [QColor](http://doc.qt.io/qt-5/qcolor.html), see the Qt documentation for that.
6. Include your class in `usercore/include/streams/all_streams.h`  
   If a file needs to include all stream object it will include `streams/all_streams.h`. Just add a line where you include the header of your class.

Now you're ready to go! Rebuild roviz with `qmake` and `make`.
