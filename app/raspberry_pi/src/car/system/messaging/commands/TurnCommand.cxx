#ifndef TURNCOMMAND_CXX
#define TURNCOMMAND_CXX

#pragma once

namespace car::system::messaging::commands {
	struct TurnCommand
	{
		float angle;
	};
};

#endif