# pi-as-keyboard

Tested on Banana Pi BPI-M2 ZERO running the 2022-09-07 Armbian jammy_edge_5.19.6_xfce_desktop image from the [official wiki page](https://wiki.banana-pi.org/Banana_Pi_BPI-M2_ZERO#Ubuntu). 

# Instruction

1. Start with a clean install of Raspbian or Ubuntu with internet/wifi configured.
2. SSH into the pi and run the following (after which the pi will power off):

```sh
curl -sSL https://raw.githubusercontent.com/alxvngn/pi-as-keyboard/master/install.sh | sudo bash -
```
3. When the pi has shut down, remove its power supply and use a regular microUSB to USB cable (non-OTG) and plug it into the USB connector marked
USB on the board (the one next to the HDMI connector). Plug other end to a computer/mac.
4. The computer/mac will recognize the pi as a generic HID USB Keyboard. It may take a while the first time so be patient.
5. Open a text editor on the target computer/mac.

# Usage

Use another computer and ssh into the pi then run:

```sh
echo 'left-shift h' | ~/pi-as-keyboard/hid-gadget-test /dev/hidg0 keyboard
echo 'i' | ~/pi-as-keyboard/hid-gadget-test /dev/hidg0 keyboard
```

Or conveniently:
```sh
~/pi-as-keyboard/sendkeys left-shift h
~/pi-as-keyboard/sendkeys i
```

7. Success! Should see **Hi** in notepad
8. Take a look at https://github.com/alxvngn/pi-as-keyboard/blob/master/hid-gadget-test.c#L20 for available keys.
