include(../usercore/base.pri)

TEMPLATE = app

UI_DIR        = $$BUILDDIR/starter/ui_header/
OBJECTS_DIR   = $$BUILDDIR/starter/obj/
MOC_DIR       = $$BUILDDIR/starter/moc/
RCC_DIR       = $$BUILDDIR/starter/rcc/
DESTDIR       = $$BUILDDIR/out
TARGET        = roviz_$$lower($$BACKEND)
LIBS         += -L$$BUILDDIR/out/usercore -l$$USERCORE_LIB

equals(PACKAGED, "true") {
    target.path     = /usr/bin
}

equals(PACKAGED, "false") {
    target.path  = /usr/local/bin
}

INSTALLS += target
