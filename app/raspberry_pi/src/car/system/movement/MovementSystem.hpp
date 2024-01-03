#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#pragma once

#include <memory>

#include "PCA9685.h"

#include "../messaging/commands/MoveCommand.hpp"
#include "../messaging/commands/TurnCommand.hpp"

using namespace car::system::messaging::commands;

namespace car::system::movement {
    constexpr int MIN_PULSE_WIDTH = 900;
    constexpr int MAX_PULSE_WIDTH = 2100;
    constexpr int FREQUENCY = 50;

    class MovementSystem
	{
	public:
        MovementSystem() {
		};

		void initalize()
		{
            this->pwm->init(1, 0x40);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            this->pwm->setPWMFreq(FREQUENCY);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

		void start()
		{
		}

		void terminate() {
		}

		~MovementSystem() {
		};

	private:
        std::unique_ptr<PCA9685> pwm;
	};
};

#endif