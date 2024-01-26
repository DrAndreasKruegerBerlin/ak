#pragma once

#include <stdexcept>
#include <limits>

namespace com
{

	template<typename To, typename From>inline To cast(const From from)
	{
		const To to = static_cast<To>(from);
		if (static_cast<From>(to) != from)
		{
			throw std::runtime_error("cast error");
		}
		return to;
	}

}
