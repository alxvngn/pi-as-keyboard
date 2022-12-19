#!/usr/bin/env bash

# If this is run from SSH, your connection will disconnect when this script is done.

HOME=/home/pi/pi-as-keyboard

if [ "$1" == "autoinstall" ]; then
  git clone https://github.com/alxvngn/pi-as-keyboard $HOME
fi

if ! grep 'dtoverlay=dwc2' /boot/config.txt; then
  echo "dtoverlay=dwc2" | sudo tee -a /boot/config.txt
fi

if ! grep dwc2 /etc/modules; then
  echo "dwc2" | sudo tee -a /etc/modules
fi

$HOME/enableHIDRCLocal.sh

#poweroff
