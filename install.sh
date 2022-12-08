#!/usr/bin/env bash

# If this is run from SSH, your connection will disconnect when this script is done.

git clone https://github.com/alxvngn/pi-as-keyboard

if ! grep 'dtoverlay=dwc2' /boot/config; then
  echo "dtoverlay=dwc2" | sudo tee -a /boot/config.txt
fi

if ! grep dwc2 /etc/modules; then
  echo "dwc2" | sudo tee -a /etc/modules
fi

./pi-as-keyboard/enableHIDRCLocal.sh

poweroff
