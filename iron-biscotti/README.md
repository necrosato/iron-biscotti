# Iron Biscotti USB Drive

## Keystroke Injection

The C++ code writes out and saves all files necessary for the iron biscotti launch daemon to run, then loads the daemon.
This includes the setup of ssh keys with proper permissions.

## Using the ATMEGA32U4 in macOS Single User Mode

Normally, flashing the arduino using `Keyboard.h` does not work to inject keystrokes into a mac running in single 
user mode. This is because the arduino normally shows up as a usb device **and** a serial port.
This causes the device to not function properly, with keystrokes not being recognized by the host.

To get around this issue, some AVR core files must be changed, as well as the HID library.
I used the modifications found at https://github.com/gdsports/usb-metamorph/tree/master/USBSerPassThruLine

After eliminating the serial port from the arduino, the device will not be able to be flashed through the IDE.
To reflash the device, the bootloader must be enabled by pulling the RST pin down twice in less than 750 milliseconds.
The device will remain in bootloader mode for 8 seconds, during which time the serial port will become
available to the IDE.

For the changes to take effect, the `HID` folder should be moved to the working `libraries` folder for the 
Arduino IDE installation.

Source: https://forum.arduino.cc/index.php?topic=545288.msg3717028#msg3717028
