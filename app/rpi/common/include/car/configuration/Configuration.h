#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#pragma once

#include <optional>
#include <string>

#include <tl/expected.hpp>

namespace car::configuration
{
	struct Configuration
	{
		std::string car_name;
		std::string host;
        std::string code;
	};
};

#endif