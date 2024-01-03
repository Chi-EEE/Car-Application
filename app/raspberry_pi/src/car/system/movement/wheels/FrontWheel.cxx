#ifndef FRONTWHEEL_CXX
#define FRONTWHEEL_CXX

#include <algorithm>

#include <PCA9685.h>
#include <spdlog/spdlog.h>

namespace car::system::movement::wheels
{
	class FrontWheel {
	private:
		/**
		 * Following method clamps the x to in_min and in_max.
		 * Afterwards, it puts the result of that into the range of out_min and out_max
		*/
		static int map(int x, int in_min, int in_max, int out_min, int out_max)
		{
			return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
		}

		static constexpr int MIN_PULSE_WIDTH = 900;
		static constexpr int MAX_PULSE_WIDTH = 2100;
		static constexpr int FREQUENCY = 50;

	public:
		FrontWheel(std::shared_ptr<PCA9685> pwm, int channel) : pwm(pwm), channel(channel) {
		}

		// Some of the code was from: https://github.com/chaoticmachinery/pca9685
		int getAnalogAngle() const
		{
			float pulse_wide = map(this->angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
			int analog_angle = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
			return analog_angle;
		}

		int getAngle() const
		{
			return this->angle;
		}

		// Some of the code was from: https://github.com/chaoticmachinery/pca9685
		int setAngle(const int& angle)
		{
			this->angle = std::clamp(angle, 0, 180);
			int analog_angle = getAnalogAngle();
			this->pwm->setPWM(channel, 0, analog_angle);
			spdlog::info("Channel: {} \tAngle: {} \tAnalog Angle: {}", this->channel, angle, analog_angle);
			return (0);
		}

	private:
		const std::shared_ptr<PCA9685> pwm;
		const int channel;

		int angle;
	};
} // namespace car::system::movement::wheels

#endif