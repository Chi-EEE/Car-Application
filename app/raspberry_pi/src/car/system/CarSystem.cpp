#include "CarSystem.h"

namespace car::system
{
	CarSystem::CarSystem(
		const std::string &websocket_url,
		std::unique_ptr<LidarDevice> lidar_device,
		std::unique_ptr<MessagingSystem> messaging_system,
		std::unique_ptr<MovementSystem> movement_system) : lidar_device(std::move(lidar_device)), messaging_system(std::move(messaging_system)), movement_system(std::move(movement_system))
	{
	}

	CarSystem::~CarSystem()
	{
		this->stop();
	}

	void CarSystem::initialize()
	{
		this->messaging_system->initialize();
		this->lidar_device->initialize();

		this->messaging_system->move_command_signal.connect([this](const MoveCommand move_command)
															{ this->move(move_command); });

		this->messaging_system->turn_command_signal.connect([this](const TurnCommand turn_command)
															{ this->turn(turn_command); });
	}

	void CarSystem::start()
	{
		if (!this->running) {
			this->messaging_system->start();
			this->lidar_device->start();
			this->running = true;
		}
	}

	void CarSystem::stop()
	{
		if (!this->running)
		{
			this->messaging_system->stop();
			this->lidar_device->stop();
			this->running = false;
		}
	}

	void CarSystem::update()
	{
		if (!this->running)
		{
			return;
		}
		json output_json;
		output_json["data"] = json::array();
		std::vector<Measure> scan = this->lidar_device->scan();
		for (const Measure &measure : scan)
		{
			output_json["data"].push_back(
				{
					{"distance", measure.distance},
					{"angle", measure.angle},
				});
		}
		this->messaging_system->sendMessage(output_json.dump());
	}

	void CarSystem::move(const MoveCommand &move_command)
	{
		this->movement_system->move(move_command);
	}

	void CarSystem::turn(const TurnCommand &turn_command)
	{
		this->movement_system->turn(turn_command);
	}
}