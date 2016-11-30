include(../plugin.pri)

HEADERS += \
           factory_TEMPLATE_FILE.h \
           TEMPLATE_FILE_item.h
SOURCES += \
           factory_TEMPLATE_FILE.cpp \
           TEMPLATE_FILE_item.cpp

RESOURCES += res.qrc
OTHER_FILES += TEMPLATE_FILE.json
LIBS += -lopencv_imgproc -lopencv_core
