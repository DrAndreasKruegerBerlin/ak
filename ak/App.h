#pragma once


#include "../ak/IScene.h"
#include "../ak/IView.h"
#include "../win/AppBase.h"
#include "../d3d/Device.h"
#include "../win/Timer.h"
#include "../com/Chrono.h"
#include <string>
#include <memory>

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

	public:
		App(const std::wstring& name, d3d::Context& context, ScenePtrType&& pScene, ViewPtrType&& pView);
		virtual ~App();
		virtual std::optional<LRESULT> passEvent(const win::Event& ev);

	private:
		std::optional<LRESULT> doCreate(const win::Event& ev);
		std::optional<LRESULT> doTimer(const win::Event& ev);
		std::optional<LRESULT> doPaint(const win::Event& ev);

	private:
		d3d::Device       device_;
		win::Timer        timer_;
		ScenePtrType      pScene_;
		ViewPtrType       pView_;
		TimePoint         last_;
		TimePoint         start_;
	};

}
