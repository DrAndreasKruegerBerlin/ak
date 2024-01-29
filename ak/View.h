#pragma once

#include <Windows.h>
#include "../ak/IView.h"
#include <memory>


namespace ak
{
	class ViewImpl;

	class View final : public IView
	{
	public:
		View();
		virtual ~View();
		void init(int width, int height);
		void render(d3d::Device& dev, int width, int height);

	private:
		std::unique_ptr<ViewImpl> pImpl_{ std::make_unique<ViewImpl>() };
	};

}
