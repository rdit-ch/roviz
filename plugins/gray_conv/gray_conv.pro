include(../plugin.pri)

HEADERS += factory_gray_conv.h \
           gray_conv_item.h

SOURCES += factory_gray_conv.cpp \
           gray_conv_item.cpp

RESOURCES += res.qrc
OTHER_FILES += gray_conv.json
LIBS += -lopencv_imgproc -lopencv_core
