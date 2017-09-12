include(../plugin.pri)

HEADERS += factory_sobel.h \
           sobel_item.h

SOURCES += factory_sobel.cpp \
           sobel_item.cpp

RESOURCES += res.qrc
OTHER_FILES += sobel.json
LIBS += -lopencv_imgproc -lopencv_core
