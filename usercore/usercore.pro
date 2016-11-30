include(usercore.pri)

SOURCES     +=  \
                src/usercore.cpp \
                src/core/abstract_robot_item.cpp \
                src/core/abstract_robot_item_p.cpp \
                src/core/image_stream.cpp \
                src/core/message_stream.cpp \
                src/core/stream_to_image_input_mapper.cpp \
                src/core/stream_to_message_input_mapper.cpp \
                src/gui/config_dialog.cpp \
                src/gui/dock_widget_signaling.cpp \
                src/gui/image_widget.cpp \
                src/gui/shared_window.cpp \
                src/gui/slider_label.cpp \
                src/portable/image_queue.cpp \
                src/portable/portable_item.cpp \
                src/portable/portable_item_p.cpp \
                src/portable/portable_image.cpp \
                src/portable/portable_image_mutable.cpp \
                src/portable/portable_image_p.cpp \
                src/core/point_stream.cpp \
                src/core/pointcloud.cpp \
                src/core/pointcloud_p.cpp \
                src/core/message.cpp \
                src/core/message_p.cpp

HEADERS     +=  \
                include/usercore.h \
                include/core/abstract_robot_item.h \
                include/core/abstract_robot_item_p.h \
                include/core/image_stream.h \
                include/core/message_stream.h \
                include/core/robot_core.h \
                include/core/stream_to_image_input_mapper.h \
                include/core/stream_to_message_input_mapper.h \
                include/gui/config_dialog.h \
                include/gui/dock_widget_signaling.h \
                include/gui/image_widget.h \
                include/gui/shared_window.h \
                include/gui/slider_label.h \
                include/portable/image_queue.h \
                include/portable/portable_item.h \
                include/portable/portable_item_global.h \
                include/portable/portable_item_p.h \
                include/portable/portable_image.h \
                include/portable/portable_image_mutable.h \
                include/portable/portable_image_p.h \
                include/core/point_stream.h \
                include/core/pointcloud.h \
                include/core/pointcloud_p.h \
                include/core/message.h \
                include/core/message_p.h

RESOURCES   +=  resources.qrc
LIBS        += -lopencv_core
