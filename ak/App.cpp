#include "../ak/App.h"
#include "../win/Event.h"
#include "../win/Painter.h"
#include "../deb/Debug.h"
#include <stdexcept>

namespace ak
{

	App::App(const std::wstring& name, d3d::Context& context, ScenePtrType&& pScene, ViewPtrType&& pView)
		: win::AppBase(name, context)
		, device_{}
		, timer_{}
		, pScene_{ std::move(pScene) }
		, pView_{ std::move(pView) }
		, last_{}
		, start_{}
	{
		// do nothing
	}

	App::~App()
	{
		// do nothing
	}

	std::optional<LRESULT> App::passEvent(const win::Event& ev)
	{
		switch (ev.msg_)
		{
		case WM_CREATE:
			return doCreate(ev);
		case WM_TIMER:
			return doTimer(ev);
		case WM_PAINT:
			return doPaint(ev);
		case WM_ERASEBKGND:
			return { 0 };
		default:
			break;
		}
		return {};
	}

	std::optional<LRESULT> App::doCreate(const win::Event& ev)
	{
		if (device_)
		{
			throw std::runtime_error("device already used");
		}

		RECT rectClient;
		::GetClientRect(ev.hWnd_, &rectClient);

		device_ = context_.createDevice(ev.hWnd_);
		pView_->init(rectClient.right - rectClient.left, rectClient.bottom - rectClient.top);
		pScene_->init(device_);
		last_ = start_ = Clock::now();
		timer_.set(ev.hWnd_, std::chrono::milliseconds(50));
		return { 0 };
	}

	std::optional<LRESULT> App::doTimer(const win::Event& ev)
	{
		BOOL ok = 0;
		ok = ::InvalidateRect(ev.hWnd_, nullptr, TRUE);
		return { 0 };
	}

	std::optional<LRESULT> App::doPaint(const win::Event& ev)
	{
		win::Painter painter(ev.hWnd_);

		TimePoint tp = Clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(tp - last_);
		deb::Debug() << "Rendering (diff:" << diff << ")................";

		const PAINTSTRUCT& ps = painter.getPs();

		device_.clear();
		device_.beginScene();
		pView_->render(device_, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);
		pScene_->render(device_, tp, start_);
		device_.endScene();
		device_.present();

		last_ = tp;
		return { 0 };
	}

}
