#include <iostream>
#include <thread>

#include "PCA9685.h"
#include "TB6612.h"

#include "pigpio.h"
#include "pigpiod_if2.h"

void setupGPIOMotor();

class BackWheels
{
private:
    static constexpr int motor_A = 17;
    static constexpr int motor_B = 27;

    static constexpr int pwm_A = 4;
    static constexpr int pwm_B = 5;

public:
    BackWheels(const int &bus_number = 1)
    {
        this->pwm.init(bus_number, 0x40);
        this->right_wheel = std::make_unique<tb6612::Motor>(tb6612::Motor(motor_A, pwm_A, forward_A));
        this->left_wheel = std::make_unique<tb6612::Motor>(tb6612::Motor(motor_B, pwm_B, forward_B));
    }

    void forward()
    {
        this->right_wheel->forward();
        this->left_wheel->forward();
    }

    void backward()
    {
        this->right_wheel->backward();
        this->left_wheel->backward();
    }

    void stop()
    {
        this->right_wheel->stop();
        this->left_wheel->stop();
    }

    void setSpeed(int speed)
    {
        this->right_wheel->setSpeed(speed);
        this->left_wheel->setSpeed(speed);
        this->speed = speed;
    }

private:
    bool forward_A = true;
    bool forward_B = true;

    std::unique_ptr<tb6612::Motor> right_wheel;
    std::unique_ptr<tb6612::Motor> left_wheel;

    PCA9685 pwm = PCA9685();

    int speed = 0;
};

int main()
{
    std::cout << "Initializing\n";
    gpioInitialise();
    std::cout << "Completed Initializing\n";
    BackWheels wheels;
    std::cout << "Started wheels\n";
    wheels.setSpeed(10);
    std::cout << "Set speed\n";
    wheels.forward();
    std::cout << "Moving forward\n";
    return 0;
}