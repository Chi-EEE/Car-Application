#ifndef TB6612_H
#define TB6612_H

#pragma once

#include "cppgpio.hpp"

namespace tb6612
{
    class Motor
    {
    public:
        Motor(
            const int &direction_channel,
            const int &pwn = 0,
            const bool &offset = true) : 
            direction_channel(direction_channel), 
            pwm(pwm), 
            offset(offset),
            forward_offset(offset),
            backward_offset(!offset)
        {
        }

    private:
        const int direction_channel;
        const int pwm;
        const bool offset;

        bool forward_offset;
        bool backward_offset;

        int speed = 0;
    }
}

#endif