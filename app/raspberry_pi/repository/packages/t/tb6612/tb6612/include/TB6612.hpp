#ifndef TB6612_H
#define TB6612_H

#pragma once

// Made with the help of ChatGPT

#include "pigpio.h"
#include "pigpiod_if2.h"

class TB6612
{
public:
    TB6612(int motor_pin, int pwm_pin) : motor_pin(motor_pin), pwm_pin(pwm_pin), offset(1)
    {
        gpioSetMode(this->motor_pin, PI_OUTPUT);
        gpioSetMode(this->pwm_pin, PI_OUTPUT);
        gpioWrite(this->motor_pin, 0);
        gpioPWM(this->pwm_pin, 0);
    }

    void setPWM(int value)
    {
        gpioPWM(this->pwm_pin, value);
    }

    void forward()
    {
        gpioWrite(this->motor_pin, this->offset);
    }

    void backward()
    {
        gpioWrite(this->motor_pin, 1 - this->offset);
    }

    void stop()
    {
        gpioWrite(this->motor_pin, 0);
        gpioPWM(this->pwm_pin, 0);
    }

    void setOffset(int offset)
    {
        this->offset = offset;
    }

private:
    int motor_pin;
    int pwm_pin;
    int offset;
};

#endif