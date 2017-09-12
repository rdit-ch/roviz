include(../usercore/base.pri)

CONFIG += plugin

PLUGIN_NAME  = $$basename(_PRO_FILE_PWD_)
UI_DIR       = $$BUILDDIR/plugins/$$PLUGIN_NAME/ui_header/
OBJECTS_DIR  = $$BUILDDIR/plugins/$$PLUGIN_NAME/obj/
MOC_DIR      = $$BUILDDIR/plugins/$$PLUGIN_NAME/moc/
RCC_DIR      = $$BUILDDIR/plugins/$$PLUGIN_NAME/rcc/
DESTDIR      = $$BUILDDIR/out/plugins
LIBS        += -L$$BUILDDIR/out/usercore -l$$USERCORE_NAME

equals(PACKAGED, true) {
    target.path = /usr/lib/roviz/$$lower($$BACKEND)
}

equals(PACKAGED, false) {
    target.path = /usr/local/lib/roviz/$$lower($$BACKEND)
}

INSTALLS += target
