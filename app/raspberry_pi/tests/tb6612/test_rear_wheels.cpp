#include <pigpio.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <algorithm>

#include "PCA9685.h"
#include "TB6612.hpp"

static constexpr int Motor_A = 17;
static constexpr int Motor_B = 27;
static constexpr int PWM_A = 4;
static constexpr int PWM_B = 5;

// Made with the help of ChatGPT

class BackWheels
{
public:
    BackWheels(const int &bus_number = 1) : left_wheel(std::make_unique<TB6612>(Motor_A, PWM_A)),
                                             right_wheel(std::make_unique<TB6612>(Motor_B, PWM_B))
    {
        this->forward_A = true;
        this->forward_B = true;

        std::cout << "Initializing PCA9685" << std::endl;
        this->pca9685.init(bus_number, 0x40);

        this->speed = 0;
    }

    void forward()
    {
        this->left_wheel->forward();
        this->right_wheel->forward();
        std::cout << "Forward" << std::endl;
    }

    void backward()
    {
        this->left_wheel->backward();
        this->right_wheel->backward();
        std::cout << "Backward" << std::endl;
    }

    void stop()
    {
        this->left_wheel->stop();
        this->right_wheel->stop();
        std::cout << "Stop" << std::endl;
    }

    int getSpeed() const
    {
        return this->speed;
    }

    void setSpeed(const int &speed)
    {
        this->speed = std::clamp(speed, 0, 100);
        const int pulse_wide = (this->speed / 100.0f) * 4095;
        this->pca9685.setPWM(PWM_A, 0, pulse_wide);
        this->pca9685.setPWM(PWM_B, 0, pulse_wide);
        std::cout << "Set speed to " << this->speed << std::endl;
    }

    void ready()
    {
        this->left_wheel->setOffset(this->forward_A);
        this->right_wheel->setOffset(this->forward_B);
        this->stop();
        std::cout << "Ready" << std::endl;
    }

    void calibration()
    {
        this->setSpeed(50);
        this->forward();
        this->cali_forward_A = this->forward_A;
        this->cali_forward_B = this->forward_B;
        std::cout << "Calibration" << std::endl;
    }

    void caliLeft()
    {
        this->cali_forward_A = (1 + this->cali_forward_A) & 1;
        this->left_wheel->setOffset(this->cali_forward_A);
        this->forward();
        std::cout << "CaliLeft" << std::endl;
    }

    void caliRight()
    {
        this->cali_forward_B = (1 + this->cali_forward_B) & 1;
        this->right_wheel->setOffset(this->cali_forward_B);
        this->forward();
        std::cout << "CaliRight" << std::endl;
    }

    void caliOK()
    {
        this->forward_A = this->cali_forward_A;
        this->forward_B = this->cali_forward_B;
        this->stop();
        std::cout << "CaliOK" << std::endl;
    }

private:
    std::unique_ptr<TB6612> left_wheel;
    std::unique_ptr<TB6612> right_wheel;
    PCA9685 pca9685;
    int forward_A;
    int forward_B;
    int cali_forward_A;
    int cali_forward_B;
    int speed;
};

void test()
{
    std::cout << "Initializing GPIO" << std::endl;
    gpioInitialise();
    BackWheels back_wheels;
    const float DELAY = 0.01f;
    try
    {
        back_wheels.forward();
        for (int i = 0; i <= 100; ++i)
        {
            back_wheels.setSpeed(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DELAY * 1000)));
        }
        for (int i = 100; i >= 0; --i)
        {
            back_wheels.setSpeed(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DELAY * 1000)));
        }

        back_wheels.backward();
        for (int i = 0; i <= 100; ++i)
        {
            back_wheels.setSpeed(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DELAY * 1000)));
        }
        for (int i = 100; i >= 0; --i)
        {
            back_wheels.setSpeed(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DELAY * 1000)));
        }
    }
    catch (...)
    {
    }
    back_wheels.stop();
    std::cout << "Terminating GPIO" << std::endl;
    gpioTerminate();
}

int main()
{
    test();
    return 0;
}
