#ifndef TB6612_H
#define TB6612_H

#pragma once

#include "pigpio.h"
#include "pigpiod_if2.h"

namespace tb6612
{
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

    private:
        const int direction_channel;
        const int pwm;
        const bool offset;

        const bool forward_offset;
        const bool backward_offset;

        const int frequency;

        int speed = 0;
    }
}

#endif