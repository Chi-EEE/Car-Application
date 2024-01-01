#include <thread>

#include "TB6612.h"

#include "pigpio.h"
#include "pigpiod_if2.h"

void setupGPIOMotor();

using namespace tb6612;

class BackWheels {
private:
    static constexpr int motor_A = 17;
    static constexpr int motor_B = 27;

    static constexpr int pwm_A = 4;
    static constexpr int pwm_B = 5;
public:
    BackWheels(const int &bus_number = 1) : pwm(bus_number) {

    }

    void forward() {
        this->motor_A.forward();
        this->motor_B.forward();
    }

    void backward() {
        this->motor_A.backward();
        this->motor_B.backward();
    }

    void stop() {
        this->motor_A.stop();
        this->motor_B.stop();
    }

    void setSpeed(int speed) {
        this->motor_A.setSpeed(speed);
        this->motor_B.setSpeed(speed);
        this->speed = speed;
    }

private:
    bool forward_A = true;
    bool forward_B = true;

    TB6612 motor_A = TB6612(motor_A, pwm_A, forward_A);
    TB6612 motor_B = TB6612(motor_B, pwm_B, forward_B);

    PCA9685 pwm;

    int speed = 0;
}


int main()
{
    setupGPIOMotor();
    return 0;
}

void setupGPIOMotor()
{
    int directionChannel;

    gpioSetMode(directionChannel, PI_OUTPUT);

    int pinA = 12;
    int pinB = 13;
    int frequency = 1000;

    gpioSetMode(pinA, PI_OUTPUT);
    gpioSetMode(pinB, PI_OUTPUT);
    int a = gpioHardwarePWM(pinA, frequency, 0);
    int b = gpioHardwarePWM(pinB, frequency, 0);

    int value = 0;

    gpioHardwarePWM(pinB, frequency, static_cast<int>(value));
    gpioHardwarePWM(pinA, frequency, static_cast<int>(value));

}