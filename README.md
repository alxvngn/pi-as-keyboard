# pi-as-keyboard

Tested on Banana Pi BPI-M2 ZERO running the 2022-09-07 Armbian jammy_edge_5.19.6_xfce_desktop image from the [official wiki page](https://wiki.banana-pi.org/Banana_Pi_BPI-M2_ZERO#Ubuntu). 

# Installation

1. Start with a clean install of Raspberry Pi OS or Ubuntu with internet/wifi configured.
2. SSH into the pi and run the following:

```sh
curl -sSL https://raw.githubusercontent.com/alxvngn/pi-as-keyboard/master/install.sh | sudo bash -
```
3. Once the installation is finished, shutdown the pi, remove its power supply and use a regular microUSB to USB cable (non-OTG) to plug it into the USB connector marked
USB on the board (the one next to the HDMI connector). Plug other end to a computer/mac.

The computer/mac will recognize the pi as a generic HID USB Keyboard. Open a text editor on the target computer/mac and test it.

# Instruction

Use another computer and ssh into the pi then run:

```sh
echo 'left-shift h' | ~/pi-as-keyboard/hid-keyboard /dev/hidg0 keyboard
echo 'i' | ~/pi-as-keyboard/hid-keyboard /dev/hidg0 keyboard
```

Or conveniently:
```sh
~/pi-as-keyboard/sendkeys left-shift h
~/pi-as-keyboard/sendkeys i
```

Success! Should see **Hi** in notepad
Take a look at https://github.com/alxvngn/pi-as-keyboard/blob/master/hid-keyboard.c#L20 for available keys.
