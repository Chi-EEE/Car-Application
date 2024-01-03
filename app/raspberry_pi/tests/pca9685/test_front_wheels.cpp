// Includes for PCA9685
#include "PCA9685.h"
#include <iostream>
#include <stdio.h>
// #include <ncurses.h>
#include <thread> // std::thread
#include <vector> // std::vector
#include <unistd.h>
#include <string>

#include <string.h>

#define MIN_PULSE_WIDTH 900
#define MAX_PULSE_WIDTH 2100
#define FREQUENCY 50

using namespace std;

int offset = 0;

// motor channels
int chanh = 0;
int chanv = 1;

// Declaration of Functions used ==================================
int setAngle(int &angle, PCA9685 pwm, int &channel);

// def map(self, x, in_min, in_max, out_min, out_max):
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

// def _angle_to_analog(self, angle):
int setAngleToAnalog(int angle)
{
    float pulse_wide;
    int analog_value;

    pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
    return (analog_value);
}

int setAngle(int &angle, PCA9685 pwm, int &channel)
{
    int val = 0;

    if (angle > 180)
    {
        angle = 179;
    }
    if (angle < 0)
    {
        angle = 1;
    }

    val = setAngleToAnalog(angle);
    // not sure what offset does
    val += offset;

    // setPWM(self, channel, on, off
    // channel: The channel that should be updated with the new values (0..15)
    // on: The tick (between 0..4095) when the signal should transition from low to high
    // off:the tick (between 0..4095) when the signal should transition from high to low

    pwm.setPWM(channel, 0, val);
    // usleep(30);
    cout << "Channel: " << channel << "\tSet to angle: " << angle << "\tVal: " << val << endl;
    return (0);
}

int main()
{

    int homeh = 90;
    int homev = 90;

    // make sure you use the right address values.
    PCA9685 pwm;
    pwm.init(1, 0x40);
    usleep(1000 * 100);
    cout << "Setting frequency: " << FREQUENCY << endl;
    pwm.setPWMFreq(FREQUENCY);
    usleep(1000 * 1000);

    cout << "Returning to HOME position." << endl;
    setAngle(homeh, pwm, chanh);
    setAngle(homev, pwm, chanv);

    return 0;
}