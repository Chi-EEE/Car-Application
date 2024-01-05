#ifndef MOVEMENTSYSTEM_CXX
#define MOVEMENTSYSTEM_CXX

#pragma once

#include <memory>

#include "../messaging/commands/MoveCommand.cxx"
#include "../messaging/commands/TurnCommand.cxx"

#include "controller/AbstractWheelController.cxx"

using namespace car::system::movement::controller;
using namespace car::system::messaging::commands;

namespace car::system::movement {
	class MovementSystem
	{
	public:
		MovementSystem(std::unique_ptr<AbstractWheelController> wheel_controller) : wheel_controller(std::move(wheel_controller))
		{
		};

		void initialize()
		{
			this->wheel_controller->initialize();
		}

		void start()
		{
		}

		void terminate() {
		}

		void move(const MoveCommand& move_command) {
			this->wheel_controller->move(move_command);
		}

		void turn(const TurnCommand& turn_command) {
			this->wheel_controller->turn(turn_command);
		}

		~MovementSystem() {
		};

	private:
		std::unique_ptr<AbstractWheelController> wheel_controller;
	};
};

#endif