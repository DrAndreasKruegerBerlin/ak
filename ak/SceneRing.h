#pragma once

#include "../ak/IScene.h"
#include "../d3d/VertexBuffer.h"

namespace ak
{

	class SceneRing final : public IScene
	{
	public:
		SceneRing() = default;
		virtual ~SceneRing() = default;
		void init(d3d::Device & dev);
		void render(d3d::Device & dev, com::TimePoint tpNow, com::TimePoint tpStart);

	private:
		d3d::VertexBuffer buffer_{};
	};

}
