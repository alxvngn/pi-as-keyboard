#!/usr/bin/env bash

# Please run this as root

HOME=/home/pi

cp /etc/rc.local /etc/rc.local.bak

cat<<EOF > /etc/rc.local
#!/bin/sh -e

$HOME/pi-as-keyboard/rpi-hid.sh
chmod 777 /dev/hidg0

exit 0
EOF

chmod 755 /etc/rc.local
