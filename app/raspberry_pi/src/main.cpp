#include <optional>
#include <string>

#include <fmt/format.h>

#include "global/Config.hpp"

#include "car/display/CarConsole.cxx"

#include "car/system/CarSystem.h"

#include "car/system/lidar/LidarScanner.cxx"
#include "car/system/lidar/LidarDummy.cxx"

#include "car/system/movement/controller/DummyWheelController.cxx"

std::string getWebSocketUrl()
{
	std::optional<int> maybe_port = GET_CONFIG_VALUE(port);
	std::string host_name;
	if (maybe_port.has_value())
	{
		host_name = fmt::format("{}:{}", GET_CONFIG_VALUE(host), maybe_port.value());
	}
	else
	{
		host_name = GET_CONFIG_VALUE(host);
	}
	return fmt::format("ws://{}/ws/room?request=join&type=car&room_name={}", host_name, GET_CONFIG_VALUE(room));
}

int main()
{
	using namespace car::display;
	using namespace car::system;
	using namespace car::system::lidar;
	using namespace car::system::messaging;
	using namespace car::system::movement::controller;
	using namespace rplidar;

	// spdlog::set_level(spdlog::level::off);

	std::string websocket_url = getWebSocketUrl();
	spdlog::info("Got websocket url: {}", websocket_url);

	std::unique_ptr<LidarDummy> scanner = std::make_unique<LidarDummy>();
	// auto maybe_scanner = LidarScanner::create(GET_CONFIG_VALUE(lidar_port));
	// if (!maybe_scanner.has_value())
	// {
	// 	spdlog::error("Unable to connect to the Lidar Scanner");
	// }
	// std::unique_ptr<LidarScanner> &scanner = maybe_scanner.value();

	std::unique_ptr<MessagingSystem> messaging_system = std::make_unique<MessagingSystem>(websocket_url);

	std::unique_ptr<MovementSystem> movement_system = std::make_unique<MovementSystem>(std::make_unique<DummyWheelController>());

	auto car_system = std::make_unique<CarSystem>(
		websocket_url,
		std::move(scanner),
		std::move(messaging_system),
		std::move(movement_system));

	// The CarConsole object will display the UI and handle user input:
	CarConsole car_console(std::move(car_system));
	car_console.run();
	return 0;
}
