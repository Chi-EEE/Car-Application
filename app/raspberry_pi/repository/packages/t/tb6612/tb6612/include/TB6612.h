#ifndef TB6612_HPP
#define TB6612_HPP

#pragma once

// Made with the help of ChatGPT

#include "pigpio.h"
#include "pigpiod_if2.h"

class TB6612
{
public:
    TB6612(int motor_pin, int pwm_pin);

    void setPWM(int value);

    void forward();

    void backward();

    void stop();

    void setOffset(int offset);

private:
    int motor_pin;
    int pwm_pin;
    int offset;
};

#endif