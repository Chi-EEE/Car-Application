# Raspberry Pi

This sub-project handles all the logic of the Sunfounder Raspberry Pi.

The system is broken down to 3 sub systems:
- lidar - Handles the lidar scanner of the Raspberry Pi
- messaging - Handles the websocket of the Raspberry Pi
- movement - Handles the movement of the Sunfounder Raspberry Pi

The system is then displayed by the `CarConsole`.

## Installation

Run the following command to build the sub-project: 

```
xmake build raspberry_pi
```

## Main Technologies

- C++17
- [ixwebsocket](https://github.com/machinezone/IXWebSocket)
- [ftxui](https://github.com/ArthurSonzogni/FTXUI)
- [nlohmann_json](https://github.com/nlohmann/json)

## Setting up Raspberry Pi

If you want to setup the raspberry pi, you can go to `SETUP.md`