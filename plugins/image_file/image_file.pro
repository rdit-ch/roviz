include(../plugin.pri)

HEADERS += factory_image_file.h \
           image_file_item.h

SOURCES += factory_image_file.cpp \
           image_file_item.cpp

RESOURCES += res.qrc
OTHER_FILES += image_file.json
LIBS += -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_core
