include(../plugin.pri)

HEADERS += factory_canny.h \
           canny_item.h

SOURCES += factory_canny.cpp \
           canny_item.cpp

RESOURCES += res.qrc
OTHER_FILES += canny.json
LIBS += -lopencv_imgproc -lopencv_core
