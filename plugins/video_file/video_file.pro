include(../plugin.pri)

HEADERS += factory_video_file.h \
           video_file_item.h

SOURCES += factory_video_file.cpp \
           video_file_item.cpp

RESOURCES += res.qrc
OTHER_FILES += video_file.json
LIBS += -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_core
