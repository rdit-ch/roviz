
!defined(BACKEND, var) {
    error(Please specify a backend)
}

!defined(PACKAGED, var) {
    PACKAGED = false
}

!defined(INSTALLDOCS, var) {
    INSTALLDOCS = false
}

CONFIG         += c++11
TEMPLATE        = lib
VERSION        += 0.1
QMAKE_CXXFLAGS += -fvisibility=hidden  # to enforce usage of USERCORE_EXPORT
USERCORE_NAME   = roviz_$$lower($$BACKEND)

INCLUDEPATH += $$PROJECT_ROOT/usercore/include

# Propagate the selected backend to the code
DEFINES += ROVIZ_SELECTED_BACKEND=$$BACKEND

# Determine platform and build target
unix: {
    PLATFORM           = linux
    USERCORE_LIB       = $$USERCORE_NAME
    ITEMFRAMEWORK_LIB  = itemframework
    QMAKE_LFLAGS      += -Wl,-rpath,/usr/local/lib
}

win32: {
    PLATFORM           = win
    USERCORE_LIB       = $$USERCORE_NAME0
    ITEMFRAMEWORK_LIB  = itemframework0
}

CONFIG(release, debug|release): {
    BUILDTARGET = release
}
CONFIG(debug, debug|release): {
    BUILDTARGET = debug
}

# The directory where everything (except the itemframework) will be built in
BUILDDIR = $$PROJECT_ROOT/build/$$lower($$BACKEND)/$$PLATFORM/$$BUILDTARGET

equals(BACKEND, "Dev") {
    # The itemframework needs some additional modules
    QT += gui xml sql widgets

    ITEMFRAMEWORK_BASE  = $$PROJECT_ROOT/itemframework/itemframework
    ITEMFRAMEWORK_DEST  = $$ITEMFRAMEWORK_BASE/build/$$PLATFORM/$$BUILDTARGET
    INCLUDEPATH        += $$ITEMFRAMEWORK_BASE/include

    # We can't influence the builddir of the itemframework
    LIBS += -L$$ITEMFRAMEWORK_DEST -l$$ITEMFRAMEWORK_LIB
}

equals(BACKEND, "Cmdline"){
    QT -= core gui
}
