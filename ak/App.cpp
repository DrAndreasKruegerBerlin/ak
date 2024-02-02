#include "../ak/App.h"
#include "../win/Event.h"
#include "../win/Painter.h"
#include "../deb/Debug.h"
#include <stdexcept>

namespace ak
{

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
			return doEraseBkgnd(ev);
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
		for (auto& it : arrScene_)
			it->init(device_);
		last_ = start_ = Clock::now();
		timer_.set(ev.hWnd_, std::chrono::milliseconds(50));
		return { 0 };
	}

	std::optional<LRESULT> App::doTimer(const win::Event& ev)
	{
		BOOL ok = ::InvalidateRect(ev.hWnd_, nullptr, TRUE);
		return { 0 };
	}

	std::optional<LRESULT> App::doEraseBkgnd(const win::Event& ev)
	{
		return { 0 };
	}

	std::optional<LRESULT> App::doPaint(const win::Event& ev)
	{
		win::Painter painter(ev.hWnd_);

		const TimePoint tp = Clock::now();
		const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(tp - last_);
		deb::Debug() << getName() << ":Rendering start (diff:" << diff << ")";

		const PAINTSTRUCT& ps = painter.getPs();

		device_.clear();
		device_.beginScene();
		pView_->render(device_, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);
		for (auto& it : arrScene_)
			it->render(device_, tp, start_);
		device_.endScene();
		device_.present();

		deb::Debug() << getName() << ":Rendering end (tot:" << std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - tp) << ")";
		last_ = tp;
		return { 0 };
	}

}
