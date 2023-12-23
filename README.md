# Car Application

Full-Stack Application used by Users to control a SunFounder Pi-Car

## Description

The application contains the following inside the app directory: 
- backend: The server behind the frontend, it allows the users and car to communicate to eachother.
- frontend: The frontend of the application, allows users to see the UI of the car,
- raspberry-pi: The code for the raspberry pi, it allows the raspberry pi to communicate to the server and handle messages from it

## Getting Started

### Dependencies

* [XMake](https://xmake.io/#/guide/installation) - Buildsystem for C++
* [Node.js](https://nodejs.org/en) - Used to build the frontend
* [pnpm](https://pnpm.io/installation) - Used to cache the dependencies from npm

### Executing program

To build the backend / raspberry_pi folder, you would have to run the following command:
```
xmake
```
This will automatically install all the dependencies from the folder and build the executable file.

## Authors

[@Chi-EEE](https://github.com/Chi-EEE)

## License

This project is licensed under the MIT License - see the LICENSE.md file for details

## Acknowledgments

[README Template](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc)