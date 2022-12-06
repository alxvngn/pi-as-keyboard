#!/usr/bin/env bash

# If this is run from SSH, your connection will disconnect when this script is done.

git clone https://github.com/alxvngn/pi-as-keyboard
cd pi-as-keyboard
./setup-hid-modules.sh
./enableHIDRCLocal.sh
poweroff
