#ifndef REARWHEEL_CXX
#define REARWHEEL_CXX

#include <memory>

#include <spdlog/spdlog.h>

#include <PCA9685.h>
#include <TB6612.h>

// Made with the help of ChatGPT

namespace car::system::movement::wheels
{
	class RearWheel {
	private:
		static constexpr int Motor_A = 17;
		static constexpr int Motor_B = 27;
		static constexpr int PWM_A = 4;
		static constexpr int PWM_B = 5;
	public:
		RearWheel(std::shared_ptr<PCA9685> pwm, std::unique_ptr<TB6612> motor) :
			pwm(pwm),
			motor(std::move(motor))
		{
			this->forward_A = true;

			this->speed = 0;
		}

			void forward()
		{
			this->motor->forward();
		}

		void backward()
		{
			this->motor->backward();
		}

		void stop()
		{
			this->motor->stop();
		}

		int getSpeed() const
		{
			return this->speed;
		}

		void setSpeed(const int& speed)
		{
			this->speed = std::clamp(speed, 0, 100);
			const int pulse_wide = (this->speed / 100.0f) * 4095;
			this->pwm->setPWM(PWM_A, 0, pulse_wide);
		}

		void ready()
		{
			this->motor->setOffset(this->forward_A);
			this->stop();
		}

		void calibration()
		{
			this->setSpeed(50);
			this->forward();
			this->cali_forward = this->forward_A;
		}

		void caliLeft()
		{
			this->cali_forward = (1 + this->cali_forward) & 1;
			this->motor->setOffset(this->cali_forward);
			this->forward();
		}

		void caliOK()
		{
			this->forward_A = this->cali_forward;
			this->stop();
		}

	private:
		std::shared_ptr<PCA9685> pwm;
		std::unique_ptr<TB6612> motor;

		int forward_A;
		int cali_forward;
		int speed;
	};
} // namespace car::system::movement::wheels

#endif