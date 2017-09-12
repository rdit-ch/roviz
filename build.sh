#!/bin/bash

USAGE=\
"./build.sh [-dh] [backends]

This script builds the roviz framework with the specified backends, or all default backends if none is specified.

 -d  Build the documentation

 -h  Show this help"

BUILDDOCS=false

while getopts :dh opt; do
    case $opt in
        d)
            BUILDDOCS=true
            ;;
        h)
            echo "$USAGE"
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            echo "$USAGE"
            exit 1 
            ;;
    esac
done
shift $((OPTIND-1))

if [[ "$BUILDDOCS" = true ]]; then
    # If we wanted to use 'make docs', we would have to run qmake with
    # a random backend first, which is rather ugly. Or run it with every
    # backend, which is very redundant
    if ! doxygen; then
        echo "Failed to build documentation" >&2
        exit 1
    fi
fi

if [[ -z "$@" ]]; then
    BACKENDS="Dev Cmdline"
else
    BACKENDS=$@
fi

for BACKEND in $BACKENDS; do
    if ! (qmake -r BACKEND="$BACKEND" && make -j 4); then
        echo "Failed to build backend $BACKEND" >&2
        exit 1
    fi
done

exit 0
