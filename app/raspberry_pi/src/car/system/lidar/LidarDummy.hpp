#ifndef LIDARDUMMY_HPP
#define LIDARDUMMY_HPP

#pragma once

#include <fstream>

#include <spdlog/spdlog.h>

#include "LidarDevice.hpp"

namespace car::system::lidar {
	class LidarDummy : public LidarDevice
	{
	public:
		LidarDummy()
		{
			spdlog::warn("Currently using the LidarDummy");
		};

		void initialize() const override {};

		void start() const override {};

		std::vector<Measure> scan() const override
		{
			std::vector<Measure> measures;
			return measures;
		};

		void terminate() const override {};

	private:

	};
}

#endif