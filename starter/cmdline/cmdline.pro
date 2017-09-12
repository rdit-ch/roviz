include(../starter.pri)

SOURCES +=  main.cpp \
            item_loader.cpp \
            project_parser.cpp

HEADERS +=  item_loader.h \
            project_parser.h

LIBS += -ldl -ltinyxml2
