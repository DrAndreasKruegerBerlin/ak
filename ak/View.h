#pragma once

#include <Windows.h>
#include <memory>

namespace d3d { class Device; }

namespace ak
{
	class ViewImpl;

	class View
	{
	public:
		View() = default;
		~View();
		void init(int width, int height);
		void render(d3d::Device& dev, int width, int height);

	private:
		ViewImpl* pImpl_{ nullptr };
	};

}
