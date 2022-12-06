# pi-as-keyboard

Tested on Banana Pi BPI-M2 ZERO running the 2022-09-07 Armbian jammy_edge_5.19.6_xfce_desktop image from the [official wiki page](https://wiki.banana-pi.org/Banana_Pi_BPI-M2_ZERO#Ubuntu).

# Instruction

1. Started with a clean install of Raspbian Buster
2. Used a Raspberry Pi 3 to setup wifi/keyboard/enable SSH/apt update etc.
3. Then took SD card out and put into Pi Zero W and booted.
4. SSHed into Pi and ran the following (after which the pi will power off):

```sh
curl -sSL https://raw.githubusercontent.com/alxvngn/pi-as-keyboard/master/install.sh | sudo bash -
```
5. When pi is off, remove power supply and use a regular (non-OTG) microUSB to USB cable and plug it in to the USB connector marked
USB on the board(the one next to the HDMI connector). Plug other end to Windows PC.
6. Be patient, eventually Windows sees it as a Generic USB keyboard (ignore device malformed warnings)
7. On the host computer, open notepad
8. Using another computer, I ssh'd into pi and ran 

```sh
cd pi-as-keyboard
echo 'left-shift h' | ./hid-gadget-test /dev/hidg0 keyboard
echo 'i' | ./hid-gadget-test /dev/hidg0 keyboard
```

or alternatively
```sh
/home/pi/pi-as-keyboard/sendkeys.sh left-shift h
/home/pi/pi-as-keyboard/sendkeys.sh i
```

9. Success! Should see **Hi** in notepad
10. Look at https://github.com/alxvngn/pi-as-keyboard/blob/master/hid-gadget-test.c#L20 for what is possible.
