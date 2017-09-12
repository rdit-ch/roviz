include(usercore.pri)

SOURCES +=  src/usercore.cpp \
            src/backend_dev/config_impl_dev.cpp \
            src/backend_dev/roviz_item_dev_base.cpp \
            src/backend_dev/roviz_item_dev_base_p.cpp \
            src/backend_dev/stream_to_input_mapper.cpp \
            src/backend_dev/trim_dev_base.cpp \
            src/backend_dev/trim_dev_base_p.cpp \
            src/backend_dev/stream_dev_base.cpp \
            src/config/config.cpp \
            src/config/config_p.cpp \
            src/core/input_queue.cpp \
            src/core/roviz_item.cpp \
            src/core/template_decl.cpp \
            src/core/trim.cpp \
            src/gui/dock_widget_signaling.cpp \
            src/gui/image_widget.cpp \
            src/gui/shared_window.cpp \
            src/streams/image.cpp \
            src/streams/image_m.cpp \
            src/streams/image_p.cpp \
            src/streams/message.cpp \
            src/streams/message_m.cpp \
            src/streams/stream.cpp \
            src/streams/stream_object.cpp

HEADERS +=  include/usercore.h \
            include/backend_dev/config_impl_dev.h \
            include/backend_dev/config_impl_dev_base.h \
            include/backend_dev/roviz_item_dev_base.h \
            include/backend_dev/roviz_item_dev_base_p.h \
            include/backend_dev/stream_to_input_mapper.h \
            include/backend_dev/trim_dev_base.h \
            include/backend_dev/trim_dev_base_p.h \
            include/backend_dev/stream_dev_base.h \
            include/config/config.h \
            include/config/config_base.h \
            include/config/config_p.h \
            include/config/config_storage_type.h \
            include/config/file_path.h \
            include/core/export_handling.h \
            include/core/input_queue.h \
            include/core/roviz_item.h \
            include/core/roviz_item_p.h \
            include/core/strong_typedef.h \
            include/core/template_decl.h \
            include/core/template_decl_helpers.h \
            include/core/trim.h \
            include/core/typedecl.h \
            include/gui/dock_widget_signaling.h \
            include/gui/image_widget.h \
            include/gui/shared_window.h \
            include/streams/all_streams.h \
            include/streams/image.h \
            include/streams/image_m.h \
            include/streams/image_p.h \
            include/streams/message.h \
            include/streams/message_m.h \
            include/streams/message_p.h \
            include/streams/stream.h \
            include/streams/stream_object.h \
            include/streams/stream_object_p.h

RESOURCES   +=  resources.qrc
LIBS        += -lopencv_core
