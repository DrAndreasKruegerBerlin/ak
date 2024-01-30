#pragma once


#include "../ak/IScene.h"
#include "../ak/IView.h"
#include "../win/AppBase.h"
#include "../d3d/Device.h"
#include "../win/Timer.h"
#include "../com/Chrono.h"
#include <string>
#include <memory>
#include <vector>

// forward references
namespace d3d { class Context; }

namespace ak
{

	class App : public win::AppBase
	{
	public:
		using Clock = com::Clock;
		using TimePoint = com::TimePoint;
		using ScenePtrType = std::unique_ptr<ak::IScene>;
		using ViewPtrType = std::unique_ptr<ak::IView>;
		using SceneArrType = std::vector<std::shared_ptr<ak::IScene> >;

	public:
		App() = default;
		virtual ~App() = default;
		template<typename ... Scene>
		App(const std::wstring& name, d3d::Context& context, ViewPtrType&& pView, Scene&& ... scene)
			: AppBase(name, context)
			, pView_{ std::move(pView) }
			, arrScene_{ {std::move(scene)...} }
		{
			// do nothing
		}
		virtual std::optional<LRESULT> passEvent(const win::Event& ev);

	private:
		std::optional<LRESULT> doCreate(const win::Event& ev);
		std::optional<LRESULT> doTimer(const win::Event& ev);
		std::optional<LRESULT> doPaint(const win::Event& ev);

	private:
		d3d::Device       device_{};
		win::Timer        timer_{};
		ViewPtrType       pView_{};
		SceneArrType      arrScene_{};
		TimePoint         last_{};
		TimePoint         start_{};
	};

}
