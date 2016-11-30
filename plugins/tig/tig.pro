include(../plugin.pri)

HEADERS += \
           factory_tig.h \
           tig_item.h
SOURCES += \
           factory_tig.cpp \
           tig_item.cpp

RESOURCES += res.qrc
OTHER_FILES += tig.json
LIBS += -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_core
