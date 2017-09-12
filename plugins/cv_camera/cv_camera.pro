include(../plugin.pri)

HEADERS += factory_cv_camera.h \
           cv_camera_item.h

SOURCES += factory_cv_camera.cpp \
           cv_camera_item.cpp

RESOURCES += res.qrc
OTHER_FILES += cv_camera.json
LIBS += -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_core
