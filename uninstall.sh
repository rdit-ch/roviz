#!/bin/bash

# Check for root
if [[ "$(id -u)" != "0" ]]; then
   echo "This script must be run as root" >&2
   exit 1
fi

rm -r /usr/local/lib/roviz /usr/local/lib/libroviz* /usr/local/bin/roviz* /usr/local/share/doc/roviz 2> /dev/null

exit 0
