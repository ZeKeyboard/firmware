# Firmware

In order to build the firmware, you need to install the Arduino IDE (to get the libraries). Go to [this page](https://www.arduino.cc/en/software) and download an Arduino IDE version 2+.

Open the IDE and go to Preferences > Additional board manager URLs. Paste the following link there:
```
https://www.pjrc.com/teensy/package_teensy_index.json
```

Go to Boards manager and install the package Teensy, version 1.59.0.

Next, install FastLED (3.6.0), OctoWS2811 (1.5.0) and SD (1.2.4).

For the simulator, you need to install `SFML`. On Ubuntu:
```
sudo apt install libsfml-dev
```

In order to upload the code, you need `teensy_loader_cli`, one that supports Teensy 4.1. On Ubuntu:

```
sudo apt install teensy_loader_cli
```

To build and upload the firmware, use
```
make upload
```

To run the simulator, go to the simulator folder and run

```
make && ./simulator
```

To run the tests, use

```
make test
```
