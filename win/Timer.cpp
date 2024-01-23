#include "../win/Timer.h"
#include <stdexcept>

namespace win
{

	Timer::~Timer()
	{
		kill();
	}

	void Timer::set(HWND hWnd, const UINT ms)
	{
		if (nullptr == hWnd_)
		{
			hWnd_ = hWnd;
		}
		else if (hWnd != hWnd_)
		{
			throw std::runtime_error("set timer (wnd)");
		}
		UINT_PTR ret = ::SetTimer(hWnd_, int(hWnd_), ms, nullptr);
		if (0 == ret)
		{
			throw std::runtime_error("set timer (api)");
		}
	}

	void Timer::kill()
	{
		if (nullptr != hWnd_)
		{
			const BOOL ok = ::KillTimer(hWnd_, int(hWnd_));
			hWnd_ = nullptr;
		}
	}

	HWND Timer::getHWnd() const
	{
		return hWnd_;
	}

}
