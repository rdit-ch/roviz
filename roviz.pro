TEMPLATE  = subdirs
CONFIG   += ordered

# We have to build the itemframework before the usercore
equals(BACKEND, "Dev") {
    SUBDIRS += itemframework
}

SUBDIRS  += usercore \
            plugins

# Qt Creator won't find the files otherwise
PROJECT_ROOT=$$PWD

# Propagate the selected backend to the code
DEFINES += ROVIZ_SELECTED_BACKEND=$$BACKEND

# The starters have to be last
equals(BACKEND, "Dev") {
    SUBDIRS += starter/dev
}

equals(BACKEND, "Cmdline") {
    SUBDIRS += starter/cmdline
}
