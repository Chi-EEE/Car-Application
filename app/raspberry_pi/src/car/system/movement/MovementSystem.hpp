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

        // https://www.arduino.cc/en/Reference/Map
        int map(int x, int in_min, int in_max, int out_min, int out_max) {
            return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
        }

        int setAngleToAnalog(int angle) {
            float pulse_wide;
            int analog_value;

            pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
            analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
            return (analog_value);
        }

		void turn(const TurnCommand& command) {
            const float angle = std::clamp(command.angle, 1.0f, 179.0f);
            for (int channel = 0; channel < 2; channel++) {
                int val = 0;
                val = setAngleToAnalog(angle);
                this->pwm->setPWM(channel, 0, val);
			}
		}

		~MovementSystem() {
		};

	private:
        std::unique_ptr<PCA9685> pwm;
	};
};

#endif