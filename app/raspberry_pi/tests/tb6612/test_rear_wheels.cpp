#include <thread>

#include "pigpio.h"
#include "pigpiod_if2.h"

void setupGPIOMotor();

int main()
{
    setupGPIOMotor();
    return 0;
}

void setupGPIOMotor()
{
    int directionChannel;

    gpioSetMode(directionChannel, PI_OUTPUT);

    int pinA = 12;
    int pinB = 13;
    int frequency = 1000;

    gpioSetMode(pinA, PI_OUTPUT);
    gpioSetMode(pinB, PI_OUTPUT);
    int a = gpioHardwarePWM(pinA, frequency, 0);
    int b = gpioHardwarePWM(pinB, frequency, 0);

    int value = 0;

    gpioHardwarePWM(pinB, frequency, static_cast<int>(value));
    gpioHardwarePWM(pinA, frequency, static_cast<int>(value));

}