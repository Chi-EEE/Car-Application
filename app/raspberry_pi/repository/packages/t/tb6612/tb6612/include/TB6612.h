#ifndef TB6612_H
#define TB6612_H

#pragma once

#include "pigpio.h"
#include "pigpiod_if2.h"

namespace tb6612
{
    enum MotorStatus
    {
        UNINITIALIZED,
        FORWARD,
        BACKWARD
    };
    class Motor
    {
    public:
        Motor(
            const int &direction_channel,
            const int &pwn = 0,
            const bool &offset = true,
            const int &frequency = 1000);

        void setSpeed(int speed);
        void forward();
        void backward();
        void stop();

        MotorStatus getStatus() const { return this->status; }
        int getSpeed() const { return this->speed; }
        bool isMoving() const { return this->speed > 0; }

    private:
        const int direction_channel;
        const int pwm;
        const bool offset;

        const bool forward_offset;
        const bool backward_offset;

        const int frequency;

        MotorStatus status = UNINITIALIZED;
        int speed = 0;
    }
}

#endif