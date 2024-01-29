#pragma once

#include "../com/Chrono.h"

namespace d3d { class Device; }

namespace ak
{

	class IScene
	{
	public:
		IScene() = default;
		virtual ~IScene() = default;
		virtual void init(d3d::Device& dev) = 0;
		virtual void render(d3d::Device& dev, com::TimePoint tpNow, com::TimePoint tpStart) = 0;
	};

}
