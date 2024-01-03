#ifndef CONFIG_CXX
#define CONFIG_CXX

#pragma once

#include <iostream>
#include <fstream>
#include <variant>
#include <optional>

// See README.md for more information
#include "nlohmann/json.hpp"

#define GET_CONFIG_VALUE(x) global::Config::getInstance().x

using json = nlohmann::json;

namespace global
{
	/**
	 * @brief Singleton class for the global configuration
	 * 
	 */
	class Config
	{
	public:
		Config(Config const&) = delete;
		Config& operator=(Config const&) = delete;
		static Config& getInstance()
		{
			static Config instance;
			return instance;
		}
	public:
		std::string lidar_port;

		std::string host;
		std::optional<int> port;

		std::string name;
		std::string room;
	private:
		Config()
		{
			this->load();
		}
		void load()
		{

			std::ifstream config_file("settings/config.jsonc");
			if (!config_file)
			{
				std::cerr << "Unable to open 'settings/config.jsonc'\n";
			}
			try
			{
				json config_json = json::parse(config_file, nullptr, true, true);
				
				this->lidar_port = config_json["lidar_port"].get<std::string>();

				this->host = config_json["host"].get<std::string>();
				
				this->port = std::make_optional<int>(config_json["port"].get<int>());

				this->name = config_json["name"].get<std::string>();

				this->room = config_json["room"].get<std::string>();
			}
			catch (const std::exception& e)
			{
				std::string error = "Error loading JSON from file: " + std::string(e.what());
				std::cerr << error << '\n';
				throw std::runtime_error(error);
			}
		}
	};
};

#endif