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

HEADERS +=  src/backend_dev/config_impl_dev.h \
            src/backend_dev/config_impl_base_dev.h \ \
            src/backend_dev/config_parent.h \
            src/backend_dev/roviz_item_base_dev.h \
            src/backend_dev/roviz_item_base_dev_p.h \
            src/backend_dev/startup_init.h \
            src/backend_dev/trim_impl_dev.h \
            src/gui/dock_widget_signaling.h \
            src/gui/image_widget.h \
            src/gui/message_widget.h \
            src/gui/shared_window.h \
            src/gui/sparse_widget.h \
            src/gui/stream_widget.h
}

equals(BACKEND, "Cmdline") {
SOURCES +=  src/backend_cmdline/config_impl_cmdline.cpp \
            src/backend_cmdline/roviz_item_base_cmdline.cpp \
            src/backend_cmdline/trim_impl_cmdline.cpp

HEADERS +=  src/backend_cmdline/config_impl_cmdline.h \
            src/backend_cmdline/config_impl_base_cmdline.h \
            src/backend_cmdline/roviz_item_base_cmdline.h \
            src/backend_cmdline/roviz_item_base_cmdline_p.h \
            src/backend_cmdline/trim_impl_cmdline.h
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
            src/streams/stream_object.cpp \
            src/streams/sparse.cpp \
            src/streams/sparse_m.cpp \
            src/streams/sparse_types.cpp \
    src/backend_dev/global_config.cpp \
    src/gui/config_dialog.cpp \
    src/config/project_config.cpp

HEADERS +=  include/usercore.h \
            include/config/config.h \ \
            include/config/file_path.h \
            include/core/export_handling.h \
            include/core/input.h \
            include/core/output.h \
            include/core/roviz_item.h \
            include/core/trim.h \
            include/streams/image.h \
            include/streams/image_m.h \
            include/streams/message.h \
            include/streams/message_m.h \
            include/streams/sparse.h \
            include/streams/sparse_m.h \
            include/streams/sparse_types.h \
            src/config/config_impl.h \
            src/config/config_storage_type.h \
            src/core/input_p.h \
            src/core/output_p.h \
            src/core/roviz_item_p.h \
            src/core/template_decl.h \
            src/core/trim_impl.h \
            src/streams/all_streams.h \
            src/streams/image_p.h \
            src/streams/message_p.h \
            src/streams/stream_object.h \
            src/streams/stream_object_p.h \
            src/streams/sparse_p.h \
    src/backend_dev/global_config.h \
    src/gui/config_dialog.h \
    src/config/project_config.h

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
