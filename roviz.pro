TEMPLATE =  subdirs
CONFIG   += ordered
SUBDIRS  += itemframework \
            usercore \
            plugins \
            starter

# Qt Creator won't find the files otherwise
PROJECT_ROOT=$$PWD
