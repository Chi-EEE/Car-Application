#include "TB6612.h"

namespace tb6612
{
    Motor::Motor(const int &direction_channel, const int &pwn, const bool &offset, const int &frequency)
        : direction_channel(direction_channel),
          pwm(pwm),
          offset(offset),
          forward_offset(offset),
          backward_offset(!offset),
          frequency(frequency)
    {
        gpioSetMode(direction_channel, PI_OUTPUT);
    }

    Motor::setSpeed(int speed)
    {
        this->speed = speed;
        gpioHardwarePWM(pwm, 1000, speed);
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