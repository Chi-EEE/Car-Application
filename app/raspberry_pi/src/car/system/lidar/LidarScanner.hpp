#ifndef LIDARSCANNER_HPP
#define LIDARSCANNER_HPP

#pragma once

#include "LidarDevice.hpp"

#include <memory>

#include <RPLidar.h>
#include <spdlog/spdlog.h>

using namespace rplidar;

namespace car::system::lidar
{
	class LidarScanner : public LidarDevice
	{
	public:
		LidarScanner(const std::string &lidar_port, const bool &enabled) : lidar(RPLidar::create(lidar_port).value()), enabled(enabled)
		{
		};

		~LidarScanner(){};

		void initialize() const override
		{
			this->lidar->reset();
			this->lidar->stop();
			this->lidar->stop_motor();
		};

		void start() const override
		{
			this->lidar->start_motor();

			// auto info_result = lidar->get_info();
			// if (!info_result.has_value()) {
			//	spdlog::error("get_info failed: {}", info_result.error());
			//	return EXIT_FAILURE;
			// }
			// auto info = info_result.value();
			// std::cout << fmt::format("model: {}, firmware: ({}, {}), hardware: {}, serial number: {}\n", info.model, info.firmware.first, info.firmware.second, info.hardware, info.serialNumber);

			// const auto health_result = lidar->get_health();
			// if (!health_result.has_value()) {
			//	spdlog::error("get_health failed: {}", health_result.error());
			//	return EXIT_FAILURE;
			// }
			// const auto health = health_result.value();
			// spdlog::info("({}, {})", health.status, health.errorCode);
		};
		std::vector<Measure> scan() const override
		{
			std::function<std::vector<Measure>()> scanGenerator = this->lidar->iter_scans();
			return scanGenerator();
		};

		void terminate() const override
		{
			this->lidar->stop();
			this->lidar->stop_motor();
			this->lidar->disconnect();
		}

	private:
		std::unique_ptr<RPLidar> lidar;
	};
}

#endif