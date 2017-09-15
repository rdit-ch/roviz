include(../plugin.pri)

HEADERS += factory_config_message_test.h \
           config_message_test_item.h

SOURCES += factory_config_message_test.cpp \
           config_message_test_item.cpp

RESOURCES += res.qrc
OTHER_FILES += config_message_test.json
LIBS += -lopencv_imgproc -lopencv_core
