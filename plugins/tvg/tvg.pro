include(../plugin.pri)

HEADERS += factory_tvg.h \
           tvg_item.h

SOURCES += factory_tvg.cpp \
           tvg_item.cpp

RESOURCES += res.qrc
OTHER_FILES += tvg.json
LIBS += -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_core
