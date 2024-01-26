#pragma once

#include <chrono>

namespace com
{

	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::time_point<Clock>;

}
