include(base.pri)

equals(BACKEND, "Dev") {
SOURCES +=  src/backend_dev/config_impl_dev.cpp \
            src/backend_dev/roviz_item_base_dev.cpp \
            src/backend_dev/roviz_item_base_dev_p.cpp \
            src/backend_dev/startup_init.cpp \
            src/backend_dev/trim_impl_dev.cpp \
            src/gui/dock_widget_signaling.cpp \
            src/gui/image_widget.cpp \
            src/gui/message_widget.cpp \
            src/gui/shared_window.cpp \
            src/gui/sparse_widget.cpp \
            src/gui/stream_widget.cpp

HEADERS +=  include/backend_dev/config_impl_dev.h \
            include/backend_dev/config_impl_base_dev.h \
            include/backend_dev/roviz_item_base_dev.h \
            include/backend_dev/roviz_item_base_dev_p.h \
            include/backend_dev/startup_init.h \
            include/backend_dev/trim_impl_dev.h \
            include/gui/dock_widget_signaling.h \
            include/gui/image_widget.h \
            include/gui/message_widget.h \
            include/gui/shared_window.h \
            include/gui/sparse_widget.h \
            include/gui/stream_widget.h
}

equals(BACKEND, "Cmdline") {
SOURCES +=  src/backend_cmdline/config_impl_cmdline.cpp \
            src/backend_cmdline/roviz_item_base_cmdline.cpp \
            src/backend_cmdline/trim_impl_cmdline.cpp

HEADERS +=  include/backend_cmdline/config_impl_cmdline.h \
            include/backend_cmdline/config_impl_base_cmdline.h \
            include/backend_cmdline/roviz_item_base_cmdline.h \
            include/backend_cmdline/roviz_item_base_cmdline_p.h \
            include/backend_cmdline/trim_impl_cmdline.h
}

SOURCES +=  src/usercore.cpp \
            src/config/config.cpp \
            src/core/input.cpp \
            src/core/input_p.cpp \
            src/core/output.cpp \
            src/core/output_p.cpp \
            src/core/roviz_item.cpp \
            src/core/template_decl.cpp \
            src/core/trim.cpp \
            src/streams/image.cpp \
            src/streams/image_m.cpp \
            src/streams/image_p.cpp \
            src/streams/message.cpp \
            src/streams/message_m.cpp \
            src/streams/message_p.cpp \
            src/streams/stream_object.cpp \
            src/streams/sparse.cpp \
            src/streams/sparse_p.cpp \
            src/streams/sparse_m.cpp \
            src/streams/sparse_types.cpp

HEADERS +=  include/usercore.h \
            include/config/config.h \
            include/config/config_impl.h \
            include/config/config_storage_type.h \
            include/config/file_path.h \
            include/core/export_handling.h \
            include/core/input.h \
            include/core/input_p.h \
            include/core/output.h \
            include/core/output_p.h \
            include/core/roviz_item.h \
            include/core/roviz_item_p.h \
            include/core/template_decl.h \
            include/core/template_decl_helpers.h \
            include/core/trim.h \
            include/core/trim_impl.h \
            include/streams/all_streams.h \
            include/streams/image.h \
            include/streams/image_m.h \
            include/streams/image_p.h \
            include/streams/message.h \
            include/streams/message_m.h \
            include/streams/message_p.h \
            include/streams/stream_object.h \
            include/streams/stream_object_p.h \
            include/streams/sparse.h \
            include/streams/sparse_p.h \
            include/streams/sparse_m.h \
            include/streams/sparse_types.h

UI_DIR       = $$BUILDDIR/usercore/ui_header/
OBJECTS_DIR  = $$BUILDDIR/usercore/obj/
MOC_DIR      = $$BUILDDIR/usercore/moc/
RCC_DIR      = $$BUILDDIR/usercore/rcc/
DESTDIR      = $$BUILDDIR/out/usercore
TARGET       = $$USERCORE_NAME

RESOURCES  +=  resources.qrc
LIBS       += -lopencv_core

docs.target    = docs
docs.commands  = doxygen

equals(PACKAGED, "true") {
    target.path         = /usr/lib
    itemframework.path  = /usr/lib
}

equals(PACKAGED, "false") {
    target.path         = /usr/local/lib
    itemframework.path  = /usr/local/lib
}

equals(BACKEND, "Dev") {
    itemframework.files = $$ITEMFRAMEWORK_DEST/*

    INSTALLS += itemframework
}

QMAKE_EXTRA_TARGETS  += docs
INSTALLS             += target
