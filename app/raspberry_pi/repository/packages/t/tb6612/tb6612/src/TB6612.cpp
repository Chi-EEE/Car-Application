#include "TB6612.h"
#include <iostream>
#include <math.h>

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return static_cast<int>(std::roundf(((x - in_min) * (out_max - out_min) / ((in_max - in_min) * 1.0f)) + out_min));
}

namespace tb6612
{
    Motor::Motor(const int &direction_channel, const int &pwm, const bool &offset, const int &frequency)
        : direction_channel(direction_channel),
          pwm(pwm),
          offset(offset),
          forward_offset(offset),
          backward_offset(!offset),
          frequency(frequency)
    {
        gpioSetMode(direction_channel, PI_OUTPUT);
    }

    void Motor::setSpeed(const int &speed)
    {
        this->speed = speed;
        int pulse_wide = map(speed, 0, 100, 0, 4095);
        std::cout << pwm << "," << speed << "," << pulse_wide << '\n';
        gpioWrite(this->pwm, pulse_wide);
    }

    void Motor::forward()
    {
        gpioWrite(direction_channel, forward_offset);
        this->status = FORWARD;
    }

    void Motor::backward()
    {
        gpioWrite(direction_channel, backward_offset);
        this->status = BACKWARD;
    }

    void Motor::stop()
    {
        this->setSpeed(0);
    }
}