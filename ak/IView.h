#pragma once

namespace d3d { class Device; }

namespace ak
{

	class IView
	{
	public:
		IView() = default;
		virtual ~IView() = default;
		virtual void init(int width, int height) = 0;
		virtual void render(d3d::Device& dev, int width, int height) = 0;
	};

}
