#include "CarSystem.h"

namespace car::system
{
	CarSystem::CarSystem(
		const std::string& websocket_url,
		std::unique_ptr<LidarDevice> lidar_device,
		std::unique_ptr<MessagingSystem> messaging_system,
		std::unique_ptr<MovementSystem> movement_system) : lidar_device(std::move(lidar_device)), messaging_system(std::move(messaging_system)), movement_system(std::move(movement_system))
	{
	}

	void CarSystem::initialize()
	{
		this->messaging_system->initialize();
		this->lidar_device->initialize();
		this->movement_system->initialize();

		this->messaging_system->speed_command_signal.connect(
			[this](const int speed)
			{ 
				this->setRearWheelsSpeed(speed);
			}
		);

		this->messaging_system->angle_command_signal.connect(
			[this](const float angle)
			{ 
				this->setFrontWheelsAngle(angle); 
			}
		);
	}

	void CarSystem::connectToServer()
	{
		if (!this->connectedToServer) {
			this->messaging_system->start();
			this->lidar_device->start();
			this->connectedToServer = true;
		}
	}

	void CarSystem::disconnectFromServer() {
		if (this->connectedToServer) {
			this->connectedToServer = false;
			this->messaging_system->stop();
			this->lidar_device->stop();
			this->movement_system->stop();
			for (auto& plugin : this->plugins) {
				plugin.lock()->stop();
			}
		}
	}

	/// <summary>
	/// Only devices should be terminated here since deconstructor does not work when the program is terminated by the user.
	/// </summary>
	void CarSystem::terminate()
	{
		this->messaging_system->terminate();
		this->lidar_device->terminate();
		this->movement_system->terminate();
	}

	void CarSystem::update()
	{
		if (this->connectedToServer)
		{
			this->messaging_system->sendMessage(this->lidar_device->getLidarMessage());
		}
		for (std::weak_ptr<Plugin>& plugin : this->plugins) {
			plugin.lock()->update();
		}
	}

	void CarSystem::addPlugin(const std::shared_ptr<car::plugin::Plugin> plugin_)
	{
		this->plugins.push_back(plugin_);
		plugin_->init(shared_from_this());
	}

	void CarSystem::startLidarDevice()
	{
		this->lidar_device->start();
	}

	void CarSystem::stopLidarDevice()
	{
		this->lidar_device->stop();
	}

	void CarSystem::setRearWheelsSpeed(const int& speed)
	{
		this->movement_system->setRearWheelsSpeed(speed);
	}
	void CarSystem::setRearLeftWheelSpeed(const int& speed)
	{
		this->movement_system->setRearLeftWheelSpeed(speed);
	}

	void CarSystem::setRearRightWheelSpeed(const int& speed)
	{
		this->movement_system->setRearRightWheelSpeed(speed);
	}

	void CarSystem::setFrontWheelsAngle(const float& angle)
	{
		this->movement_system->setFrontWheelsAngle(angle);
	}

	void CarSystem::setCameraServo1Angle(const float& angle)
	{
		this->movement_system->setCameraServo1Angle(angle);
	
	}
	void CarSystem::setCameraServo2Angle(const float& angle)
	{
		this->movement_system->setCameraServo2Angle(angle);
	}

	void CarSystem::setRearWheelsDirectionToForward()
	{
		this->movement_system->setRearWheelsDirectionToForward();
	}

	void CarSystem::setRearLeftWheelDirectionToForward()
	{
		this->movement_system->setRearLeftWheelDirectionToForward();
	}

	void CarSystem::setRearRightWheelDirectionToForward()
	{
		this->movement_system->setRearRightWheelDirectionToForward();
	}
	
	void CarSystem::setRearWheelsDirectionToBackward()
	{
		this->movement_system->setRearWheelsDirectionToBackward();
	}

	void CarSystem::setRearLeftWheelDirectionToBackward()
	{
		this->movement_system->setRearLeftWheelDirectionToBackward();
	}

	void CarSystem::setRearRightWheelDirectionToBackward()
	{
		this->movement_system->setRearRightWheelDirectionToBackward();
	}
}