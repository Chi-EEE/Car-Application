#include "CarSystem.h"

namespace car_system {
	CarSystem::CarSystem(const std::string& websocket_url, std::unique_ptr<LidarDevice> lidar_device, std::unique_ptr<MessagingSystem> messaging_system) : lidar_device(std::move(lidar_device)), messaging_system(std::move(messaging_system))
	{
		this->initialize(websocket_url);
	}

	CarSystem::~CarSystem()
	{
		this->terminate();
	}

	void CarSystem::run()
	{
		spdlog::info("Running Car");
		this->lidar_device->start();
		while (true)
		{
			json output_json;
			output_json["data"] = json::array();
			std::vector<Measure> scan = this->lidar_device->scan();
			for (const Measure& measure : scan)
			{
				output_json["data"].push_back(
					{
					{"distance", measure.distance},
					{"angle", measure.angle},
					}
				);
			}
			this->messaging_system->send(output_json.dump());
		}
	}

	void CarSystem::initialize(const std::string& websocket_url)
	{

	}

	void CarSystem::terminate()
	{
		this->lidar_device->terminate();
		this->messaging_system->terminate();
	}

	void CarSystem::turn(float angle)
	{
	}

	void CarSystem::move(float distance)
	{
	}
}