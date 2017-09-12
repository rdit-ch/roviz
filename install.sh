#!/bin/bash

USAGE=\
"./install.sh [-pdh] [backends]

This script installs the roviz framework with the specified backends, or all default backends if none is specified.

--- Requires root access ---

 -p  Build in package mode
     The application will be installed to /usr/bin instead of /usr/bin/local

 -d  Install the documentation

 -h  Show this help"

PACKAGED=false
INSTALLDOCS=false

while getopts :pdh opt; do
    case $opt in
        p)
            PACKAGED=true
            ;;
        d)
            INSTALLDOCS=true
            ;;
        h)
            echo -e "$USAGE"
            exit 0
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            echo -e "$USAGE"
            exit 1 
            ;;
    esac
done
shift $((OPTIND-1))

# Check for root
if [[ "$(id -u)" != "0" ]]; then
   echo "This script must be run as root" >&2
   exit 1
fi

# Install documentation
if [[ "$INSTALLDOCS" = true ]]; then
    if [[ "$PACKAGED" = true ]]; then
        DOC_PATH=/usr/share/doc/roviz
    else
        DOC_PATH=/usr/local/share/doc/roviz
    fi
    
    echo -n "Installing documentation... "
    mkdir -p "$DOC_PATH"
    cp -r docs/api/* "$DOC_PATH"
    echo "Done"
fi

if [[ -z "$@" ]]; then
    BACKENDS="Dev Cmdline"
else
    BACKENDS=$@
fi

for BACKEND in $BACKENDS; do
    if ! (qmake -r PACKAGED="$PACKAGED" BACKEND="$BACKEND" && make install); then
        echo "Failed to install backend $BACKEND" >&2
        exit 1
    fi
done

exit 0
