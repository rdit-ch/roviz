include(../plugin.pri)

HEADERS += factory_harris_corner.h \
           harris_corner_item.h

SOURCES += factory_harris_corner.cpp \
           harris_corner_item.cpp

RESOURCES += res.qrc
OTHER_FILES += harris_corner.json
LIBS += -lopencv_imgproc -lopencv_core
