# Iron Biscotti

A macOS owning usb drive by Naookie Sato and Miguel Hernandez.

The goal of this project is to create a device that mimics a usb flash drive in appearance,
but can quickly aquire remote root access to a target Apple host given brief physical access.

## The Vulnerability

We will be using a keystroke injector and the target computer's single user mode to quickly install a
Launch Daemon on the target machine. This daemon will attempt to open an ssh reverse tunnel
for the root user to a remote server.

## The Device

The main attack vector for this project will be physical USB access to the target host.
The following are platfors we considered for the device:  
1. USB Rubber ducky: This microcontroller can mimic usb keyboards.
Drawbacks are its limited functionality and slower input speed in comparison to the arduino.
2. ATMEGA32U4 microcontroller: Otherwise known as the Ardiono Micro or Leonardo, this microcontroller can
use the HID protocol to emulate a USB keyboard and mouse. It has a much faster speed than the rubber ducky.
The main drawback to this device is that we cannot currently use it in single user mode. The feasibility of this
is currently being investigated.
