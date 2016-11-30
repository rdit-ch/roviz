include(../plugin.pri)

HEADERS += \
            factory_gaussian_blur.h \
            gaussian_blur_item.h

SOURCES += \
            factory_gaussian_blur.cpp \
            gaussian_blur_item.cpp

RESOURCES += res.qrc
OTHER_FILES += gaussian_blur.json
LIBS += -lopencv_imgproc -lopencv_core
