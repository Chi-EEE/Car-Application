#ifndef LIDARDUMMY_CXX
#define LIDARDUMMY_CXX

#pragma once

#include <fstream>

#include <spdlog/spdlog.h>

#include "LidarDevice.cxx"

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

		void stop() const override {};

	private:

	};
}

#endif