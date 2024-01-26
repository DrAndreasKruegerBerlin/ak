#pragma once

#include "../d3d/VertexBuffer.h"
#include "../com/Chrono.h"


namespace d3d { class Device; }

namespace ak 
{

	class Scene
	{
	public:
		Scene() = default;
		~Scene();
		void init(d3d::Device& dev);
		void render(d3d::Device& dev, com::TimePoint tpNow, com::TimePoint tpStart);

	private:
		d3d::VertexBuffer buffer_{};
	};

}
