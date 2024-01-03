// Includes for PCA9685
#include "PCA9685.h"
#include <iostream>
#include <algorithm>
#include <thread>

static constexpr int MIN_PULSE_WIDTH = 900;
static constexpr int MAX_PULSE_WIDTH = 2100;
static constexpr int FREQUENCY = 50;

using namespace std;

int offset = 0;

// motor channels
static constexpr int chanh = 0;
static constexpr int chanv = 1;

// Declaration of Functions used ==================================
int setAngle(int &angle, PCA9685 pwm, int channel);

/**
 * Following method clamps the x to in_min and in_max.
 * Afterwards, it puts the result of that into the range of out_min and out_max
*/
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

int setAngle(int &angle, PCA9685 pwm, int channel)
{
    angle = std::clamp(angle, 0, 180);

    int analog_angle = setAngleToAnalog(angle);
    // not sure what offset does
    analog_angle += offset;

    pwm.setPWM(channel, 0, analog_angle);
    cout << "Channel: " << channel << "\tSet to angle: " << angle << "\tVal: " << analog_angle << endl;
    return (0);
}

int main()
{

    int homeh = 90;
    int homev = 90;

    // make sure you use the right address values.
    PCA9685 pwm;
    pwm.init(1, 0x40);
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(1000 * 100)));
    cout << "Setting frequency: " << FREQUENCY << endl;
    pwm.setPWMFreq(FREQUENCY);
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(1000 * 1000 )));

    cout << "Returning to HOME position." << endl;
    setAngle(homeh, pwm, chanh);
    setAngle(homev, pwm, chanv);

    return 0;
}