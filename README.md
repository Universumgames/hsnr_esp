# Communication between Arduino Uno's through light

<sub>created by Tom Arlt, Florian Meyer, Henning Müller, Florian Körwer</sub>

This project is a simple Aduino Uno project for communication between two Arduinos via light and controlling them via a serial monitor.

## Installation
This project was created with PlatformIO, an extension for VS Code to write Arduino programs, compile and write the binaries to an Arduino.

To use our project, open the platformIO project, change the `upload_port` in `platformio.ini` to the port your arduino is plugged into and upload the program.

A simple wiring schematic will follow to explain the required wiring for this project to work.

## Usage
1. Once uploaded, the arduino can communicate with another one as long as they are in LOS (Line of sight) and pointing directly at each other.
2. Once placed correctly, you can start to open a serial monitor. You could use the integrated serial monitor in PlatformIO, the integrated serial monitor in the [Arduino IDE](https://www.arduino.cc/en/software) or [Putty](https://www.putty.org/), a great tool for using all kinds of connectivity like serial, ssh, raw, Telnet and Rlogin, or one of it's successors.
3. Select the Port your Arduino is plugged into, select the baud rate your arduino is sending/recieving to/from the serial monitor (the default is `115200`, but can be easily changed in `config.hpp`)
4. If everything works, you should be able to recieve encoded message from another Arduino and read the decoded result in your terminal, as well as write a message yourself and send it to the other Arduino.