#ifndef DUMMYWHEELCONTROLLER_CXX
#define DUMMYWHEELCONTROLLER_CXX

#pragma once

#include "AbstractWheelController.cxx"

namespace car::system::movement::controller
{
	class DummyWheelController : public AbstractWheelController
	{
	public:
		void initialize() {};

		void setRearWheelsSpeed(const int& speed) override {

		}

		void setFrontWheelsAngle(const float& angle) override {

		}

		void setRearLeftWheelSpeed(const int& speed) override {

		}

		void setRearRightWheelSpeed(const int& speed) override {

		}

		void setFrontLeftWheelAngle(const float& angle) override {

		}

		void setFrontRightWheelAngle(const float& angle) override {

		}

		void setRearWheelDirectionToForwards() override {

		}

		void setRearWheelDirectionToBackwards() override {

		}
	private:
	};
} // namespace car::system::movement::controller

#endif