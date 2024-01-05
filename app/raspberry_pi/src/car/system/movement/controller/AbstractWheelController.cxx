#ifndef ABSTRACTWHEELCONTROLLER_CXX
#define ABSTRACTWHEELCONTROLLER_CXX

#pragma once

#include "../../messaging/commands/MoveCommand.cxx"
#include "../../messaging/commands/TurnCommand.cxx"

using namespace car::system::messaging::commands;

namespace car::system::movement::controller
{
    class AbstractWheelController
    {
    public:
        virtual void initialize() = 0;

        virtual void move(const MoveCommand &move_command) = 0;
        virtual void turn(const TurnCommand &turn_command) = 0;

    private:
    };
} // namespace car::system::movement::controller

#endif