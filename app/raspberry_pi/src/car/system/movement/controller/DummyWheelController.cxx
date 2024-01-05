#ifndef DUMMYWHEELCONTROLLER_CXX
#define DUMMYWHEELCONTROLLER_CXX

#pragma once

#include "AbstractWheelController.cxx"

namespace car::system::movement::controller
{
    class DummyWheelController : public AbstractWheelController
    {
    public:
        void initialize(){};

        void move(const MoveCommand &move_command){};
        void turn(const TurnCommand &turn_command){};

    private:
    };
} // namespace car::system::movement::controller

#endif