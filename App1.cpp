#include "App1.h"
#include "win/Event.h"
#include "deb/Debug.h"
#include <stdexcept>


App1::App1(const std::wstring& name, d3d::Context& context)
	: win::AppBase(name, context)
	, device_{}
	, timer_{}
	, lastTimepoint_{ 0 }
{
	// do nothing
}

App1::~App1()
{
	// do nothing
}

std::optional<LRESULT> App1::passEvent(const win::Event& ev)
{
	switch (ev.msg_)
	{
	case WM_CREATE:
		return doCreate(ev);
	case WM_TIMER:
		return doTimer(ev);
	case WM_MOUSEWHEEL:
		if (getName() == L"APP2")
		{
			throw std::runtime_error("XXXXX");
		}
		if (getName() == L"APP1")
		{
			::PostQuitMessage(1000);
		}
		return {};
	default:
		break;
	}
	return {};
}

std::optional<LRESULT> App1::doCreate(const win::Event& ev)
{
	device_ = context_.createDevice(ev.hWnd_);
	timer_.set(ev.hWnd_, 20);
	return { 0 };
}

std::optional<LRESULT> App1::doTimer(const win::Event& ev)
{
	FILETIME ft{ 0 };
	GetSystemTimePreciseAsFileTime(&ft);
	unsigned long long ft64 = unsigned long long(ft.dwLowDateTime) + (unsigned long long(ft.dwHighDateTime) << 32);
	deb::Debug() << "doTimer(" << name_ << "): " << float(ft64 - lastTimepoint_)/10000;
	lastTimepoint_ = ft64;
	return { 0 };
}
