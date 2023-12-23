#include <thread>

#include "gpiod.hpp"

int main()
{

    return 0;
}

void setupGPIOMotor()
{
    int directionChannel;
    // Setup GPIO for direction channel
    gpiod::chip chip("/dev/gpiochip0");
    int direction_channel = 17;
    chip.prepare_request()
        .add_line_settings(
            gpiod::line::offset(direction_channel), gpiod::line_settings()
                                         .set_direction(gpiod::line::direction::OUTPUT) // Setup the GPIO
                                         .set_debounce_period(std::chrono::microseconds(100)) // 100 Speed
                                         .set_output_value(gpiod::line::value::ACTIVE) // Move wheel
            )
        .do_request();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    chip.prepare_request()
        .add_line_settings(
            gpiod::line::offset(direction_channel), gpiod::line_settings()
                                         .set_direction(gpiod::line::direction::OUTPUT) // Setup the GPIO
                                         .set_output_value(gpiod::line::value::INACTIVE) // Stop wheel
            )
        .do_request();
}